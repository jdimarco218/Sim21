#include <assert.h>
#include <fstream>
#include <iostream>
#include <list>
#include <memory>
#include <utility>
#include <vector>
#include "Sim.h"
#include "Deck.h"
#include "Player.h"

using std::pair;
using std::make_pair;
using std::map;
using std::string;
using std::vector;

#define DEBUG false

Sim::Sim(TSimMode simMode, TDeckType deckType)
{
    _game = std::unique_ptr<Game>(new Game(deckType));
    _dealer = std::unique_ptr<Player>(new Player());
    int numPlayers = 2;
    for(int i = 0; i < numPlayers; ++i)
    {
        _playersVec.push_back( std::unique_ptr<Player>(new Player()) );
    }
    _handsPlayed = 0;
    _shoesPlayed = 0;
    _handsToPlay = 3;
    _simMode = simMode;
    _deckType = deckType;
    _upCardIndex = 0;
    //TODO: Take these from config
    _outputDir = "results";
    _playerNames = std::vector<std::string>();
    _playerNames.push_back("Player_0");
    _playerNames.push_back("Player_1");
    _saveStatsPerShoe = 1;
}

/**
 * Writes the results of the simulation to the given directory and file
 * according to the given intervals.  Output is csv format with a special
 * delimiting string between runs: "#End of run." by default.
 */
void Sim::SaveStatistics()
{
    if (DEBUG) {std::cout << "Saving statistics." << std::endl;}

    if (_shoesPlayed % _saveStatsPerShoe == 0)
    {
        for (int i = 0; i < _playersVec.size(); ++i)
        {
            if (i < _playerNames.size())
            {
                std::ofstream outputFile(_outputDir + "/" + _playerNames[i] + ".csv");
                outputFile << _handsPlayed << ", "
                           << _shoesPlayed << ", "
                           << _playersVec[i]->GetChips()
                           << std::endl;
            }
        }

    }
    return;
}

std::unique_ptr<Player>& Sim::GetPlayerAt(int idx)
{
    assert(idx < _playersVec.size());
    return _playersVec[idx];
}

void Sim::RunSimulation()
{
    switch(_simMode)
    {
        case TSimMode::STRATEGY:
            RunStrategySimulation();
            break;
        case TSimMode::EOR:
            RunEorSimulation();
            break;
        case TSimMode::INDEX:
            RunIndexSimulation();
            break;
        default:
            break;
    }

}

void Sim::RunEorSimulation()
{
    return;
}

void Sim::RunIndexSimulation()
{
    return;
}

void Sim::RunStrategySimulation()
{
    if (DEBUG) {std::cout << "RunStrategySimulation()..." << std::endl;}

    // Start a new Game
    _game->ResetGame();

    if (DEBUG) {std::cout << "Cut card: " << _game->GetCutCardPosition() << " out of " << _game->GetCardsRemaining() << std::endl;}

    while(!IsSimulationFinished())
    {
        if (DEBUG) {std::cout << "Playing new hand..." << std::endl;}

        SimulateHand(_game.get());
        _handsPlayed++;

        if (DEBUG) {PrintChips();}
    }

    return;
}

bool Sim::IsSimulationFinished()
{
    switch(_simMode)
    {
        case TSimMode::STRATEGY:
            if(_handsPlayed < _handsToPlay)
            {
                return false;
            }
            break;
        case TSimMode::EOR:
            RunEorSimulation();
            break;
        case TSimMode::INDEX:
            RunIndexSimulation();
            break;
        default:
            break;
    }
    return true;
}

void Sim::PrintGameState(Game * game)
{
    for(auto& player : _playersVec)
    {
        std::cout << "Player hand: ";
        for(auto& hand : player->_hands)
        {
            for(auto& card : hand)
            {
                std::cout << *card << ", ";
            }
            std::cout << std::endl;
        }
    }
    std::cout << "Dealer: " << *(_dealer->_hands[0][_upCardIndex]) << std::endl;

    return;
}

void Sim::PrintChips()
{
    for(int pIdx = 0; pIdx < _playersVec.size(); ++pIdx)
    {
        std::cout << "Player[" << pIdx << "]'s chips, totalWagerd, totalWinnings: " << std::endl;
        std::cout << _playersVec[pIdx]->_chips << ", "
                  << _playersVec[pIdx]->_totalWagered << ", "
                  << _playersVec[pIdx]->_totalWinnings
                  << std::endl;
    }

    return;
}

bool Sim::IsBlackjack(const std::vector<std::unique_ptr<Card> >& hand) const
{
    bool ret = false;
    if (hand.size() == 2 && GetOptimalValue(hand) == 21)
    {
        ret = true;
    }
    return ret;
}

void Sim::CheckInsuranceAndBlackjack()
{
    bool isAceUp = IsAceUp();

    // First handle insurance if an ace is showing
    //
    for (auto& player : _playersVec)
    {
        if ( isAceUp && player->WantsInsurance(_game.get()) )
        {
            if(DEBUG){ std::cout << "db.   Player takes insurance." << std::endl; }
            player->MakeInsuranceBet();
        }

    }

    // Handle dealer's blackjack
    //
    if (_dealer->_hands[0].size() == 2 && GetOptimalValue(_dealer->_hands[0]) == 21)
    {
        if(DEBUG){ std::cout << "db.   Dealer has bj." << std::endl; }
        for (auto& player : _playersVec)
        {
            if ( isAceUp && player->WantsInsurance(_game.get()) )
            {
                PayoutPlayer(player, 0, Sim::FACTOR_INSURANCE);
            }
            if (player->_hands[0].size() == 2 && GetOptimalValue(player->_hands[0]) == 21)
            {
                // Player and dealer both have blackjack
                //
                if(DEBUG){ std::cout << "db.   Player has bj." << std::endl; }
                PayoutPlayer(player, 0, Sim::FACTOR_PUSH);
            }
            else
            {
                if(DEBUG){ std::cout << "db.   Player does not have bj." << std::endl; }
                // Player doesn't have blackjack but dealer does
            }

            // Player does not get to play
            //
            player->_activeVec[0] = false;
        }
    }
    else // Dealer does NOT have blackjack
    { 
        if(DEBUG){ std::cout << "db.   Dealer does not have bj." << std::endl; }
        for (auto &player : _playersVec)
        {
            if (player->_hands[0].size() == 2 && GetOptimalValue(player->_hands[0]) == 21)
            {
                if (DEBUG) {std::cout << "db.   Player has bj." << std::endl;}
                PayoutPlayer(player, 0, Sim::FACTOR_BLACKJACK);
                player->_activeVec[0] = false;
            }
        }
    }

    return;
}

/**
 * This function returns the lowest rank possible.
 * Aces are counted as 1 and all face cards are 10
 */
int Sim::GetMinimalValue(const std::vector<std::unique_ptr<Card> >& hand) const
{
    int sum = 0;
    bool hasAce = false;
    for (auto& Card : hand)
    {
        if (Card->GetRank() >= 10)
        {
            sum += 10;
        }
        else
        {
            sum += Card->GetRank();
        }
    }
    return sum;
}

/**
 * This function returns the best rank possible that is <= 21.
 * Aces can be 1 or 11, and all face cards are 10. 
 * If the value is > 21, then Aces count as 1 (irrelevant).
 */
int Sim::GetOptimalValue(const std::vector<std::unique_ptr<Card> >& hand) const
{
    int sum = 0;
    bool hasAce = false;
    for (auto& Card : hand)
    {
        if (Card->GetRank() == 1)
        {
            sum += 1;
            hasAce = true;
        }
        else if (Card->GetRank() >= 10)
        {
            sum += 10;
        }
        else
        {
            sum += Card->GetRank();
        }
    }
    if (hasAce && (sum + 10 <= 21))
    {
        sum += 10;
    }
    return sum;
}

void Sim::PayoutInsurance(std::unique_ptr<Player>& player)
{
    player->_totalWinnings += player->_insuranceBet->_amount;
    player->_chips += player->_insuranceBet->_amount;
    return;
}

void Sim::PayoutPlayer(std::unique_ptr<Player>& player, int handIdx, double factor)
{
    player->_totalWinnings += player->_handsBetVec[handIdx]->_amount * factor;
    player->_chips += player->_handsBetVec[handIdx]->_amount * factor;
    return;
}

bool Sim::WantsInsurance(int playerIdx)
{
    return false;
}

bool Sim::IsAceUp()
{
    return (_dealer->_hands[0][_upCardIndex]->GetRank() == 1);
}

/**
 * This function will return the std::string key for the Player's basic
 * strategy std::map. The key system uses the following hierarchy:
 *
 * For a pair, prepend "p" to one of the Card's rank
 *   - pair of 7's --> "p7"
 * For a soft hand, prepend "s" to the higher possible total
 *   - ace 5       --> "s16"
 * For all others, the integer total is used
 *   - 3 5 Jack    --> "18"
 */
std::string Sim::GetStratKey(const std::vector<std::unique_ptr<Card> >& hand) const
{
    std::string ret = "";
    if (hand.size() == 2)
    {
        int rank_0 = hand[0].get()->GetRank();
        int rank_1 = hand[1].get()->GetRank();    
        if (rank_0 > 10)
        {
            rank_0 = 10;
        }
        if (rank_1 > 10)
        {
            rank_1 = 10;
        }
        if (rank_0 == rank_1)
        {
            return "p" + std::to_string(rank_0);
        }
    }
    if (IsHandSoft(hand))
    {
        return "s" + std::to_string(GetOptimalValue(hand)); 
    }
    
    return std::to_string(GetOptimalValue(hand));
}

/**
 * Returns the _dealer's up card value. That is, Ace counts for 1
 * and all face cards count for 10.
 */
int Sim::GetUpCardRank()
{
    int ret = _dealer->_hands[0][_upCardIndex]->GetRank();
    if (ret > 10)
    {
        ret = 10;
    }
    return ret;
}

/**
 * Does a lookup of the Player's strategy decision based on
 * TODO
 */
TPlayAction Sim::GetDecision(std::unique_ptr<Player>& player,
                             std::vector<std::unique_ptr<Card> >& hand,
                             bool isFollowUp)
{

    std::string stratKey = GetStratKey(hand);
    if (DEBUG)
    {
        std::cout << "StratKey, DealerUpCard found: " 
                  << stratKey << ", " 
                  << GetUpCardRank() << " for hand" 
                  << std::endl;
        for (auto& card : hand)
        {
            std::cout << *card << ", ";
        }
        std::cout << std::endl;
    }
    
    if (isFollowUp)
    {
        return player->bs_s17_das_ls.find(stratKey)->second[GetUpCardRank()].second;
    }   
    else
    {
        return player->bs_s17_das_ls.find(stratKey)->second[GetUpCardRank()].first;
    }
}

/**
 * If an Ace can count for 1 or 11 without exceeding 21.
 */ 
bool Sim::IsHandSoft(const std::vector<std::unique_ptr<Card> >& hand) const
{
    return GetOptimalValue(hand) != GetMinimalValue(hand);
}

void Sim::PayoutWinners()
{
    for (int pIdx = 0; pIdx < _playersVec.size(); ++pIdx)
    {
        for (int hIdx = 0; hIdx < _playersVec[pIdx]->_hands.size(); ++hIdx)
        {
            if (_playersVec[pIdx]->_activeVec[hIdx])
            {
                int playerResult = GetOptimalValue(_playersVec[pIdx]->_hands[hIdx]);
                int dealerResult = GetOptimalValue(_dealer->_hands[0]);
                if (DEBUG) {std::cout << "Player has " << playerResult << " against the dealer " << dealerResult << std::endl;}
                if (playerResult <= 21)
                {
                    if (playerResult == dealerResult)
                    {
                        // Push
                        //
                        if (_playersVec[pIdx]->_doubleVec[hIdx])
                        {
                            if (DEBUG) {std::cout << "Paying player[" << pIdx << "] PUSH on a double." << std::endl;}
                            PayoutPlayer(_playersVec[pIdx], hIdx, Sim::FACTOR_PUSH);
                        }
                        else
                        {
                            if (DEBUG) {std::cout << "Paying player[" << pIdx << "] PUSH." << std::endl;}
                            PayoutPlayer(_playersVec[pIdx], hIdx, Sim::FACTOR_PUSH);
                        }
                    }
                    else if (playerResult > dealerResult || dealerResult > 21)
                    {
                        // Winner!
                        //
                        if (_playersVec[pIdx]->_doubleVec[hIdx])
                        {
                            if (DEBUG) {std::cout << "Paying player[" << pIdx << "] WIN on a double." << std::endl;}
                            PayoutPlayer(_playersVec[pIdx], hIdx, Sim::FACTOR_WIN);
                        }
                        else
                        {
                            if (DEBUG) {std::cout << "Paying player[" << pIdx << "] WIN." << std::endl;}
                            PayoutPlayer(_playersVec[pIdx], hIdx, Sim::FACTOR_WIN);
                        }
                    }
                }
                //
                // else, player's hand busted
                //
            }
            _playersVec[pIdx]->_activeVec[hIdx] = false;
        }
    }
}

void Sim::PlayDealerHand()
{
    auto& hand = _dealer->GetHand(0);

    while (GetOptimalValue(hand) < 17 ||
          (GetOptimalValue(hand) == 17 &&
           IsHandSoft(hand) &&
           !GetGame()->GetS17()) )
    {
        hand.push_back(GetGame()->DealCard());
    }

    if (DEBUG) 
    {
        std::cout << "Dealer final hand: " << std::endl;
        for (auto& card : hand)
        {
            std::cout << *card << " ";
        }
        std::cout << std::endl;
    }
}

/**
 * TODO
 */
void Sim::PlayHand(int pIdx, int hIdx)
{
    auto& player = _playersVec[pIdx];
    bool isFollowup = false;

    while (GetOptimalValue(player->_hands[hIdx]) < 21)
    {
        // Deal first card if this is a hand resulting from a split (one card)
        //
        if (player->_hands[hIdx].size() == 1)
        {
            if (DEBUG) {std::cout << "Dealing second card after split." << std::endl;}
            player->_hands[hIdx].push_back(GetGame()->DealCard());

            if (IsBlackjack(player->_hands[hIdx]))
            {
                // Payout, then finished this particular hand
                //
                if (GetGame()->GetBonusPayOnSplitAces())
                {
                    PayoutPlayer(player, hIdx, Sim::FACTOR_BLACKJACK);
                }
                else
                {
                    PayoutPlayer(player, hIdx, Sim::FACTOR_WIN);
                }
                player->_activeVec[hIdx] = false;
                break;
            }
            
            // Finished if this was an Ace and unable to play split aces
            //
            if (!GetGame()->GetPlaySplitAces() &&
                player->_hands[hIdx][0]->GetRank() == 1)
            {
                break;
            }
        }

        // At this point, the player has a two-card hand that needs a decision
        //
        auto decision = GetDecision(player, player->_hands[hIdx], isFollowup);
        if (DEBUG) {std::cout << "Decision: " << static_cast<int>(decision) << std::endl;}

        // CHECK AND HANDLE Split action
        if (decision == TPlayAction::SPLIT)
        {
            if (DEBUG) {std::cout << "Handling split action." << std::endl;}

            // The player can split if:
            //   - The number of splits has not reached the max AND
            //   - They are not a resplit aces OR resplit aces are allowed
            //
            if (player->_hands.size() < _game->GetNumSplits() &&
                (player->_hands[hIdx][0]->GetRank() != 1 ||
                 player->_hands.size() == 1 ||
                 GetGame()->GetPlaySplitAces()) )
            {
                // Player can execute split
                //
                player->_hands.push_back(std::vector<std::unique_ptr<Card> >());
                player->_activeVec.push_back(true);
                player->_doubleVec.push_back(false);

                // std::move the Card from current hand to the newest hand
                //
                int numHands = player->_hands.size();
                const auto it = player->_hands[hIdx].rbegin();
                player->_hands[numHands-1].push_back(std::move(*it));
                player->_hands[hIdx].pop_back();

                // Update the new wager/Bet
                //
                player->MakeAdditionalBet(numHands-1, player->GetHandBetAmount(hIdx)); 
            }
            else
            {
                // Player cannot split, take follow-up action
                //
                auto followup = GetDecision(player, player->_hands[hIdx], true);
                if (followup == TPlayAction::STAND)
                {
                    if (DEBUG) {std::cout << "Follow-up STAND." << std::endl;}
                    break;
                }
                else if (followup == TPlayAction::HIT)
                {
                    if (DEBUG) {std::cout << "Follow-up HIT." << std::endl;}
                    player->_hands[hIdx].push_back(GetGame()->DealCard());
                }
                else if (followup == TPlayAction::SURRENDER)
                {
                    if (DEBUG) {std::cout << "Follow-up SURRENDER." << std::endl;}
                    PayoutPlayer(player, hIdx, Sim::FACTOR_SURRENDER);
                    player->_activeVec[hIdx] = false;
                    break;
                }
                else
                {
                    std::cerr << "ERROR: Unknown followup decision after split." << std::endl;
                    exit(-1);
                }
            }
        }
        // CHECK AND HANDLE Double action
        else if (decision == TPlayAction::DOUBLE)
        {
            if (DEBUG) {std::cout << "Handling double action." << std::endl;}
            if (_deckType == TDeckType::BLACKJACK)
            { 
                if (player->_hands[hIdx].size() == 2)
                {
                    player->_hands[hIdx].push_back(GetGame()->DealCard());
                    player->_doubleVec[hIdx] = true;
                    player->MakeAdditionalBet(hIdx, player->GetHandBetAmount(hIdx)); 
                    if (DEBUG) 
                    {
                        std::cout << "Hand after: " << std::endl;
                        for (auto& card : player->_hands[hIdx])
                        {
                            std::cout << card->GetRank() << ", ";
                        }
                        std::cout << std::endl;
                    }
                    break;
                }
                else
                {
                    // Player cannot execute double, lookup follow-up action
                    //
                    if (DEBUG) {std::cout << "Unable to double" << std::endl;}
                    auto followup = GetDecision(player, player->_hands[hIdx], true);
                    if (followup == TPlayAction::STAND)
                    {
                        if (DEBUG) {std::cout << "Follow-up STAND." << std::endl;}
                        break;
                    }
                    else if (followup == TPlayAction::HIT)
                    {
                        if (DEBUG) {std::cout << "Follow-up HIT." << std::endl;}
                        player->_hands[hIdx].push_back(GetGame()->DealCard());
                    }
                    else
                    {
                        std::cerr << "ERROR: Unknown followup decision after double." << std::endl;
                        exit(-1);
                    }
                }
            }
            else
            {
                // TODO FOR SP21
                player->_hands[hIdx].push_back(GetGame()->DealCard());
                if (DEBUG)
                {
                    std::cout << "Hand after: " << std::endl;
                    for (auto& card : player->_hands[hIdx])
                    {
                        std::cout << card->GetRank() << ", ";
                    }
                    std::cout << std::endl;
                }
                break;
            }
        }
        // CHECK AND HANDLE Stand action
        else if (decision == TPlayAction::STAND)
        {
            if (DEBUG) {std::cout << "Handling stand action." << std::endl;}
            break;
        }
        // CHECK AND HANDLE Hit action
        else if (decision == TPlayAction::HIT)
        {
            if (DEBUG) {std::cout << "Handling hit action." << std::endl;}
            player->_hands[hIdx].push_back(GetGame()->DealCard());
            if (DEBUG)
            {
                std::cout << "Hand after: " << std::endl;
                for (auto& card : player->_hands[hIdx])
                {
                    std::cout << card->GetRank() << ", ";
                }
                std::cout << std::endl;
            }
        }
        // CHECK AND HANDLE Surrender action
        else if (decision == TPlayAction::SURRENDER)
        {
            // TODO handle other possible game rules
            if (player->_hands[hIdx].size() == 2)
            {
                if (DEBUG) {std::cout << "Handling surrender action." << std::endl;}
                PayoutPlayer(player, hIdx, Sim::FACTOR_SURRENDER);
                player->_activeVec[hIdx] = false;
                break;
            }
            else
            {
                // Player cannot execute surrender, lookup follow-up action
                auto followup = GetDecision(player, player->_hands[hIdx], true);
                if (followup == TPlayAction::STAND)
                {
                    if (DEBUG) {std::cout << "Follow-up STAND." << std::endl;}
                    break;
                }
                else if (followup == TPlayAction::HIT)
                {
                    if (DEBUG) {std::cout << "Follow-up HIT." << std::endl;}
                    player->_hands[hIdx].push_back(GetGame()->DealCard());
                }
                else
                {
                    std::cerr << "ERROR: Unknown followup decision after double." << std::endl;
                    exit(-1);
                }
            }
        }
        // Should never happen
        else
        {
            std::cerr << "ERROR: Unknown action!" << std::endl;
            break;
        }
    }

    // If the hand busted, set inactive. It is possible to arrive here
    // after breaking out of the loop (value < 21)
    //
    if (GetOptimalValue(player->_hands[hIdx]) > 21)
    {
        player->_activeVec[hIdx] = false;
    }

    //
    // At this point, we have handled the current hand's play. If a new
    // hand was split off then we must play the next one - recursively.
    //
    int numHands = player->_hands.size();
    if (numHands > (hIdx + 1) && (player->_hands[hIdx+1].size() == 1))
    {
        if (DEBUG) {std::cout << "Detected split, starting hand number " << hIdx + 1 << std::endl;}
        PlayHand(pIdx, hIdx + 1);
    }

    return;
}

void Sim::SimulateHand(Game * game)
{
    if (DEBUG) {std::cout << "Starting a new hand..." << std::endl;}

    // Get bets and reset players
    //
    for (auto& player : _playersVec)
    {
        player->ResetPlayer();
        player->SetInitialBet(game);
    }
    _dealer->ResetPlayer();

    // Deal all initial cards
    //
    if (DEBUG) {std::cout << "Dealing cards." << std::endl;}
    for (auto& player : _playersVec)
    {
        // Deal two cards
        player->_hands[0].push_back(game->DealCard());
        player->_hands[0].push_back(game->DealCard());
    }
    // Dealer's initial cards
    _dealer->_hands[0].push_back(game->DealCard());
    _dealer->_hands[0].push_back(game->DealCard());

    if (DEBUG)
    {
        std::cout << std::endl;
        std::cout << "Printing game state." << std::endl;
        PrintGameState(game);
        std::cout << std::endl;
    }

    // Check insurance, bonuses, sidebets, and blackjack
    //
    if (DEBUG) {std::cout << "Checking BJ & Insurance." << std::endl;}
    CheckInsuranceAndBlackjack();

    // Play each player's hand
    //
    for (int i = 0; i < _playersVec.size(); ++i)
    {
        if (_playersVec[i]->_activeVec[0])
        {
            if (DEBUG) {std::cout << "Playing player " << i << "'s hand(s)..." << std::endl;}

            PlayHand(i, 0);
        }
        else
        {
            if (DEBUG) {std::cout << "Skipping inactive player[" << i << "]." << std::endl;}
        }
    }

    // Play dealer's hand after all players
    //
    PlayDealerHand();

    // Check and payout the winners
    //
    PayoutWinners();

    return;
}
