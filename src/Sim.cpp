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

#define DEBUG true

Sim::Sim(TSimMode       simMode, 
         TDeckType      deckType,
         int            handsToPlay,
         vector<string> players,
         bool           hit17)
{
    _game = std::unique_ptr<Game>(new Game(deckType));
    _dealer = std::unique_ptr<Player>(new Player());
    _playerNames = std::vector<std::string>();
    for (auto& player : players)
    {
        _playersVec.push_back( std::unique_ptr<Player>(new Player(player)) );
        _playerNames.push_back(player);
    }
    _handsPlayed = 0;
    _shoesPlayed = 0;
    _handsToPlay = handsToPlay;
    _simMode = simMode;
    _deckType = deckType;
    _upCardIndex = 0;
    _outputDir = "results";
    _saveStatsPerShoe = 1;

    // Rules
    _game->SetH17(hit17);
}

/**
 * Writes the results of the simulation to the given directory and file
 * according to the given intervals.  Output is csv format and 
 * FinalizeStatistics() should be called finally to append the delimiting
 * string. "#End of run." by default.
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
                std::ofstream outputFile(
                                    _outputDir + "/" + _playerNames[i] + ".csv",
                                    std::ofstream::out | std::ofstream::app);
                outputFile << _playersVec[i]->GetChips() << ", "
                           << _shoesPlayed << ", "
                           << _handsPlayed << ", "
                           << _playersVec[i]->GetTotalWagered() << ", "
                           << std::endl;
            }
        }

    }
    return;
}

/**
 * Writes the results of the simulation to the given directory and file
 * according to the given intervals.  Output is csv format with a special
 * delimiting string between runs: "#End of run." by default.
 */
void Sim::FinalizeStatistics()
{
    if (DEBUG) {std::cout << "Finalizing statistics." << std::endl;}

    if (_shoesPlayed % _saveStatsPerShoe == 0)
    {
        for (int i = 0; i < _playersVec.size(); ++i)
        {
            if (i < _playerNames.size())
            {
                std::ofstream outputFile(
                                    _outputDir + "/" + _playerNames[i] + ".csv",
                                    std::ofstream::out | std::ofstream::app);
                outputFile << _playersVec[i]->GetChips() << ", "
                           << _shoesPlayed << ", "
                           << _handsPlayed << ", "
                           << _playersVec[i]->GetTotalWagered() << ", "
                           << std::endl
                           << "#End of run."
                           << std::endl;
            }
        }

    }
    return;
}

/**
 * Getter function that returns a reference to the Player
 * at the given index.
 */
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

    //
    // Start a new Game
    //
    _game->ResetGame();

    if (DEBUG) {std::cout << "Cut card: " << _game->GetCutCardPosition() << " out of " << _game->GetCardsRemaining() << std::endl;}

    while(!IsSimulationFinished())
    {
        if (_game->GetNumCardsDealt() > _game->GetCutCardPosition())
        {
            _shoesPlayed++;
            if (DEBUG) {std::cout << "Shuffle up. New Shoe." << std::endl;}
            _game = std::unique_ptr<Game>(new Game(_deckType));
            SaveStatistics();
        }
        if (DEBUG) {std::cout << "Playing new hand..." << std::endl;}

        SimulateHand(_game.get());
        _handsPlayed++;

        if (DEBUG) {PrintChips();}
    }
    FinalizeStatistics();

    return;
}

bool Sim::IsSimulationFinished()
{
    bool ret = true;

    switch(_simMode)
    {
    case TSimMode::STRATEGY:
        if(_handsPlayed < _handsToPlay)
        {
            ret = false;
        }
        break;
    case TSimMode::EOR:
        ret = true;
        break;
    case TSimMode::INDEX:
        ret = true;
        break;
    default:
        ret = true;
        break;
    }
    return ret;
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
    switch(_deckType)
    {
    case TDeckType::BLACKJACK:
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
        break;
    }
    case TDeckType::SPANISH21:
        for (auto &player : _playersVec)
        {
            if (player->_hands[0].size() == 2 && GetOptimalValue(player->_hands[0]) == 21)
            {
                if (DEBUG) {std::cout << "db.   Player has bj." << std::endl;}
                PayoutPlayer(player, 0, Sim::FACTOR_BLACKJACK);
                player->_activeVec[0] = false;
            }
        }
        break;
    default:
        std::cerr << "ERROR: Unkown decktype in CheckInsuranceAndBlackjack()" << std::endl;
        break;
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
    if (DEBUG)
    {
        std::cout << "Paying player's " << handIdx << ": "
                  << player->_handsBetVec[handIdx]->_amount
                  << " with a factor of " << factor
                  << std::endl;
    }
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
std::string Sim::GetStratKey(const std::vector<std::unique_ptr<Card> >& hand, bool hardTotal) const
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
        if (rank_0 == rank_1 && !hardTotal)
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
 * Returns the _dealer's up card suit.
 */
int Sim::GetUpCardSuit()
{
    return _dealer->_hands[0][_upCardIndex]->GetSuit();
}

bool Sim::Is678(int r0, int r1, int r2)
{
    bool ret = false;

    ret =  (r0 == 6 &&
            r1 == 7 &&
            r2 == 8)  ||

           (r0 == 6 &&
            r1 == 8 &&
            r2 == 7)  ||

           (r0 == 7 &&
            r1 == 6 &&
            r2 == 8)  ||

           (r0 == 7 &&
            r1 == 8 &&
            r2 == 6)  ||

           (r0 == 8 &&
            r1 == 6 &&
            r2 == 7)  ||

           (r0 == 8 &&
            r1 == 7 &&
            r2 == 6);

    return ret;
}

bool Sim::IsTwoOf678(int r0, int r1)
{
    bool ret = false;

    ret =  (r0 == 6 &&
           (r1 == 7 ||
            r1 == 8))  ||

           (r0 == 7 &&
           (r1 == 6 ||
            r1 == 8))  ||

           (r0 == 8 &&
           (r1 == 6 ||
            r1 == 7));

    return ret;
}

TPlayAction Sim::GetBaseDecision(TPlayAction action)
{
    TPlayAction ret = action;

    if (action == TPlayAction::DOUBLE ||
        action == TPlayAction::DOUBLE_X_3 ||
        action == TPlayAction::DOUBLE_X_4 ||
        action == TPlayAction::DOUBLE_X_5 ||
        action == TPlayAction::DOUBLE_X_6)
    {
        ret = TPlayAction::DOUBLE;
    }
    else if (action == TPlayAction::STAND ||
             action == TPlayAction::STAND_X_4 ||
             action == TPlayAction::STAND_X_5 ||
             action == TPlayAction::STAND_X_6)
    {
        ret = TPlayAction::STAND;
    }
    else if (action == TPlayAction::HIT ||
             action == TPlayAction::HIT_IF_678 ||
             action == TPlayAction::HIT_IF_S678 ||
             action == TPlayAction::HIT_IF_SP678)
    {
        ret = TPlayAction::HIT;
    }
    else if (action == TPlayAction::SPLIT_X_SUPER)
    {
        ret = TPlayAction::SPLIT;
    }

    return ret;
}

/**
 * Checks if the given Action is able to be played for the current game and
 * set of rules.
 */
bool Sim::CanTakeAction(std::unique_ptr<Player>& player, 
                        std::vector<std::unique_ptr<Card> >& hand,
                        int handIdx,
                        TPlayAction action)
{
    bool ret = false;
    switch(_deckType)
    {
    //
    // Blackjack actions
    //
    case TDeckType::BLACKJACK:
        switch(action)
        {
        case TPlayAction::DOUBLE:
            if (hand.size() == 2)
            {
                ret = true;
            }
            break;
        case TPlayAction::SURRENDER:
            if (hand.size() == 2 && _game->IsLateSurrender())
            {
                if (DEBUG) {std::cout << "CanTake(Surrender)." << std::endl;}
                ret = true;
            }
            break;
        case TPlayAction::SPLIT:
            if (player->NumHands() < _game->GetNumSplits())
            {
                if (hand[0]->GetRank() != 1 ||
                    player->_hands.size() == 1 ||
                    GetGame()->GetPlaySplitAces()) 
                {
                    ret = true;
                }
            }
            break;
        case TPlayAction::HIT:
            ret = true;
            break;
        case TPlayAction::STAND:
            ret = true;
            break;
        case TPlayAction::NONE:
        default:
            ret = false;
            break;
        }
        break;
    //
    // Spanish 21 actions
    //
    case TDeckType::SPANISH21:
        switch(action)
        {
        case TPlayAction::STAND_X_4:
            if (hand.size() < 4)
            {
                ret = true;
            }
            break;
        case TPlayAction::STAND_X_5:
            if (hand.size() < 5)
            {
                ret = true;
            }
            break;
        case TPlayAction::STAND_X_6:
            if (hand.size() < 6)
            {
                ret = true;
            }
            break;
        case TPlayAction::SPLIT_X_SUPER:
            if (CanTakeAction(player, hand, handIdx, TPlayAction::SPLIT) &&
                !(hand[0]->GetRank() == 7 &&
                  hand[1]->GetRank() == 7 &&
                  _dealer->_hands[0][0]->GetRank() == 7 &&
                  hand[0]->GetSuit() == hand[1]->GetSuit()))
            {
                ret = true;
            }
            break;
        case TPlayAction::DOUBLE_X_3:
            if (player->NumDoubles(handIdx) <= _game->GetNumDoubles() &&
                hand.size() < 3)
            {
                ret = true;
            }
            break;
        case TPlayAction::DOUBLE_X_4:
            if (player->NumDoubles(handIdx) <= _game->GetNumDoubles() &&
                hand.size() < 4)
            {
                ret = true;
            }
            break;
        case TPlayAction::DOUBLE_X_5:
            if (player->NumDoubles(handIdx) <= _game->GetNumDoubles() &&
                hand.size() < 5)
            {
                ret = true;
            }
            break;
        case TPlayAction::DOUBLE_X_6:
            if (player->NumDoubles(handIdx) <= _game->GetNumDoubles() &&
                hand.size() < 6)
            {
                ret = true;
            }
            break;
        case TPlayAction::HIT_IF_678:
            if (IsTwoOf678(hand[0]->GetRank(), hand[1]->GetRank()))
            {
                ret = true;
            }
            break;
        case TPlayAction::HIT_IF_S678:
            if (IsTwoOf678(hand[0]->GetRank(), hand[1]->GetRank()) &&
                hand[0]->GetSuit() == hand[1]->GetSuit())
            {
                ret = true;
            }
            break;
        case TPlayAction::HIT_IF_SP678:
            if (IsTwoOf678(hand[0]->GetRank(), hand[1]->GetRank()) &&
                hand[0]->GetSuit() == hand[1]->GetSuit() &&
                hand[0]->GetSuit() == static_cast<int>(TSuitType::SPADES))
            {
                ret = true;
            }
            break;
        case TPlayAction::DOUBLE:
            if (player->NumDoubles(handIdx) <= _game->GetNumDoubles())
            {
                ret = true;
            }
            break;
        case TPlayAction::SURRENDER:
            if (_game->IsLateSurrender())
            {
                if (DEBUG) {std::cout << "CanTake(Surrender)." << std::endl;}
                ret = true;
            }
            break;
        case TPlayAction::SPLIT:
            if (player->NumHands() < _game->GetNumSplits())
            {
                if (hand[0]->GetRank() != 1 ||
                    player->_hands.size() == 1 ||
                    GetGame()->GetPlaySplitAces()) 
                {
                    ret = true;
                }
            }
            break;
        case TPlayAction::HIT:
            if (player->NumDoubles(handIdx) == 0)
            {
                ret = true;
            }
            break;
        case TPlayAction::STAND:
            ret = true;
            break;
        case TPlayAction::NONE:
        default:
            ret = false;
            break;
        }
        break;
    default:
        break;
    }
    return ret;
}

void Sim::PrintDecision(TPlayAction action)
{
    if (DEBUG)
    {
        switch (action)
        {
            case TPlayAction::SURRENDER:
                std::cout << "Surrender action." << std::endl;
                break;
            case TPlayAction::DOUBLE:
                std::cout << "Double action." << std::endl;
                break;
            case TPlayAction::SPLIT:
                std::cout << "Split action." << std::endl;
                break;
            case TPlayAction::SPLIT_X_SUPER:
                std::cout << "Split except super bonus action." << std::endl;
                break;
            case TPlayAction::HIT:
                std::cout << "Hit action." << std::endl;
                break;
            case TPlayAction::STAND:
                std::cout << "Stand action." << std::endl;
                break;
            case TPlayAction::STAND_X_4:
                std::cout << "Stand except four cards action." << std::endl;
                break;
            case TPlayAction::STAND_X_5:
                std::cout << "Stand except five cards action." << std::endl;
                break;
            case TPlayAction::STAND_X_6:
                std::cout << "Stand except six cards action." << std::endl;
                break;
            case TPlayAction::DOUBLE_X_3:
                std::cout << "Double except three cards action." << std::endl;
                break;
            case TPlayAction::DOUBLE_X_4:
                std::cout << "Double except four cards action." << std::endl;
                break;
            case TPlayAction::DOUBLE_X_5:
                std::cout << "Double except five cards action." << std::endl;
                break;
            case TPlayAction::DOUBLE_X_6:
                std::cout << "Double except six cards action." << std::endl;
                break;
            case TPlayAction::HIT_IF_678:
                std::cout << "Hit if 6 7 8 action." << std::endl;
                break;
            case TPlayAction::HIT_IF_S678:
                std::cout << "Hit if 6 7 8 suited action." << std::endl;
                break;
            case TPlayAction::HIT_IF_SP678:
                std::cout << "Hit if 6 7 8 spades action." << std::endl;
                break;
            default:
                std::cout << "Unknown TPlayAction." << std::endl;
                break;
        }

    }

    return;
}

/**
 * Does a lookup of the Player's strategy decision based on
 * the game conditions and the Player's strategy. Determines
 * which decision to ultimately take.
 *
 * Returns a basic decision. That is, a decision that is not
 * conditional (e.g. STAND, SPLIT, DOUBLE, HIT, SURRENDER).
 */
TPlayAction Sim::GetDecision(std::unique_ptr<Player>& player,
                             std::vector<std::unique_ptr<Card> >& hand,
                             int handIdx)
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

    // Check if the Player deviates from basic strategy and if it applies
    //
    auto deviationStrat = player->GetDeviationStrategy(_game);
    auto it = deviationStrat.find(stratKey);
    if (player->IsDeviating() && it != deviationStrat.end())
    {
        if (it->second[GetUpCardRank()].second.first != TPlayAction::NONE) 
        {
            int indexNum = it->second[GetUpCardRank()].first;
            if ((indexNum >= 0 && _game->GetHiloTrueCount() >= indexNum) ||
                (indexNum <  0 && _game->GetHiloTrueCount() <= indexNum) )
            {
                // The deviation applies, use it
                //
                auto decision = it->second[GetUpCardRank()].second.first;
                if (DEBUG) {std::cout << "Deviating." << std::endl;}
                if (CanTakeAction(player, hand, handIdx, decision))
                {
                    decision = GetBaseDecision(decision);
                    if (DEBUG) {PrintDecision(decision);}

                    return decision;
                }
                else
                {
                    auto followUpDecision = it->second[GetUpCardRank()].second.second;
                    if (CanTakeAction(player, hand, handIdx, followUpDecision))
                    {
                        if (DEBUG) {std::cout << "Follow-up deviation." << std::endl;}
                        followUpDecision = GetBaseDecision(followUpDecision);
                        if (DEBUG) {PrintDecision(followUpDecision);}

                        return followUpDecision;
                    }
                }
            }
        }
        else
        {
            // Unable to find a deviation for the StratKey. Check the hardTotal
            // in case there is a better play for the given rules.
            //
            std::string hardStratKey = GetStratKey(hand, true);
            it = deviationStrat.find(hardStratKey);
            if (player->IsDeviating() && it != deviationStrat.end())
            {
                if (it->second[GetUpCardRank()].second.first != TPlayAction::NONE) 
                {
                    int indexNum = it->second[GetUpCardRank()].first;
                    if ((indexNum >= 0 && _game->GetHiloTrueCount() >= indexNum) ||
                        (indexNum <  0 && _game->GetHiloTrueCount() <= indexNum) )
                    {
                        // The deviation applies, use it
                        //
                        auto hardDecision = it->second[GetUpCardRank()].second.first;
                        if (DEBUG) {std::cout << "Deviating hard total." << std::endl;}
                        if (CanTakeAction(player, hand, handIdx, hardDecision))
                        {
                            hardDecision = GetBaseDecision(hardDecision);
                            if (DEBUG) {PrintDecision(hardDecision);}

                            return hardDecision;
                        }
                        else
                        {
                            auto followUpHardDecision = it->second[GetUpCardRank()].second.second;
                            if (CanTakeAction(player, hand, handIdx, followUpHardDecision))
                            {
                                followUpHardDecision = GetBaseDecision(followUpHardDecision);
                                if (DEBUG) {std::cout << "Follow-up hard total deviation." << std::endl;}
                                if (DEBUG) {PrintDecision(followUpHardDecision);}

                                return followUpHardDecision;
                            }
                        }
                    }
                }
            }
        }
    }
    
    // Check the basic strategy the Player is using
    //
    auto basicStrat = player->GetPlayStrategy(_game, hand, handIdx);
    auto decision = basicStrat.find(stratKey)->second[GetUpCardRank()].first;
    if (DEBUG) {std::cout << "Checking primary decision." << std::endl;}
    if (DEBUG) {PrintDecision(decision);}
    if (CanTakeAction(player, hand, handIdx, decision))
    {
        if (DEBUG) {std::cout << "Primary decision." << std::endl;}
        return GetBaseDecision(decision);
    }
    else
    {
        // Take the follow-up decision
        //
        auto followUpDecision = basicStrat.find(stratKey)->second[GetUpCardRank()].second;
        if (DEBUG) {std::cout << "Checking secondary decision." << std::endl;}
        if (DEBUG) {PrintDecision(basicStrat.find(stratKey)->second[GetUpCardRank()].second);}
        if (CanTakeAction(player, hand, handIdx, followUpDecision))
        {
            if (DEBUG) {std::cout << "FollowUp decision." << std::endl;}
            return GetBaseDecision(followUpDecision);
        }
        else
        {
            // Cannot take follow-up decision, which should happen very rarely.
            // We will look up the hard total as a fall-back, since hard totals
            // will not have a set of three possible distinct decisions. At the
            // moment, the final decision could be a conditional
            // (e.g. STAND_X_4), but we will check for that. If other decisions
            // arise, then vectors of decisions will need to be implemented!
            //
            auto tertiaryStratKey = GetStratKey(hand, true);
            auto tertiaryDecision = basicStrat.find(tertiaryStratKey)->second[GetUpCardRank()].first;
            if (DEBUG) {std::cout << "Checking tertiary (primary hard total) decision." << std::endl;}
            if (DEBUG) {PrintDecision(tertiaryDecision);}
            if (CanTakeAction(player, hand, handIdx, tertiaryDecision))
            {
                return GetBaseDecision(tertiaryDecision);
            }
            else
            {
                auto hardTotalFollowup = basicStrat.find(tertiaryStratKey)->second[GetUpCardRank()].second;
                if (DEBUG) {std::cout << "Checking primary hard total followup decision." << std::endl;}
                if (DEBUG) {PrintDecision(hardTotalFollowup);}
                if (CanTakeAction(player, hand, handIdx, hardTotalFollowup))
                {
                    return GetBaseDecision(hardTotalFollowup);
                }
                else
                {
                    // If we are here without knowing all possible decisions,
                    // or we cannot conditionally decide, then we have a
                    // problem. Currently we can account for STAND_X_<num>
                    //
                    if (hardTotalFollowup == TPlayAction::STAND_X_4 ||
                        hardTotalFollowup == TPlayAction::STAND_X_5 ||
                        hardTotalFollowup == TPlayAction::STAND_X_6)
                    {
                        if (DEBUG) {std::cout << "Not standing due to hand size." << std::endl;}
                        auto determinedDecision = TPlayAction::HIT;
                        if (DEBUG) {PrintDecision(determinedDecision);}
                        return determinedDecision;
                    }
                    else
                    {
                        // "I'm just gonna stand cuz I'm stupid."
                        //
                        std::cerr << "ERROR: Could not find " << player->GetName()
                                  << "'s decision for " << stratKey << " vs " << GetUpCardRank()
                                  << " and " << player->NumDoubles(handIdx) << " doubles!" << std::endl;
                       return TPlayAction::STAND; 
                    }
                }
            }
        }
    }

    // Should never get here.
    //
    return TPlayAction::STAND;
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
                        if (playerResult == 21 && _deckType == TDeckType::SPANISH21)
                        {
                            if (_deckType == TDeckType::SPANISH21)
                            {
                                auto factor = CheckForBonusPayout(pIdx, hIdx);
                                if (DEBUG) {std::cout << "Calculated win/bonus factor: " << std::to_string(factor) << std::endl;}
                                PayoutPlayer(_playersVec[pIdx], hIdx, factor);
                            }
                        }
                        else
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
                            if (_deckType == TDeckType::SPANISH21)
                            {
                                auto factor = CheckForBonusPayout(pIdx, hIdx);
                                if (DEBUG) {std::cout << "Calculated win/bonus factor: " << std::to_string(factor) << std::endl;}
                                PayoutPlayer(_playersVec[pIdx], hIdx, factor);
                            }
                            else if (_deckType == TDeckType::BLACKJACK)
                            {
                                if (DEBUG) {std::cout << "Paying player[" << pIdx << "] WIN." << std::endl;}
                                PayoutPlayer(_playersVec[pIdx], hIdx, Sim::FACTOR_WIN);
                            }
                            else
                            {
                                // should never get here
                                std::cerr << "ERROR: Unknown decktype during PayoutWinners()" << std::endl;
                            }
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

/**
 * This function returns the proper factor in the case of a bonus payout
 * for games like Spanish 21.
 *
 * Note that it should only be called for a winner and the default payout
 * is a standard win of 1:1, which equates to 2.0 the Bet since payouts
 * include the original bet amount.
 */
double Sim::CheckForBonusPayout(int playerIndex, int handIndex)
{
    auto ret = Sim::FACTOR_WIN;

    if (_deckType == TDeckType::SPANISH21)
    {
        // First, check for the super bonus
        //
        auto& hand = _playersVec[playerIndex]->_hands[handIndex];
        if (hand.size() == 3 &&
            hand[0]->GetRank() == 7 &&
            hand[1]->GetRank() == 7 &&
            hand[2]->GetRank() == 7 &&
            hand[0]->GetSuit() == hand[1]->GetSuit() &&
            hand[0]->GetSuit() == hand[2]->GetSuit() &&
            GetUpCardRank() == 7)
        {
            // We have a super bonus! Calculate the appropriate
            // factor, since it varies
            //
            // The factor is the value that will give a 1000 payout
            // if the bet is 5-24, or 5000 payout for bets of at least 25
            //
            if (_playersVec[playerIndex]->_handsBetVec[handIndex]->_amount < 25)
            {
                ret = 1000.0 / _playersVec[playerIndex]->_handsBetVec[handIndex]->_amount;
            }
            else
            {
                ret = 5000.0 / _playersVec[playerIndex]->_handsBetVec[handIndex]->_amount;
            }
        }
        else if (hand.size() == 3 &&
                 hand[0]->GetRank() == 7 &&
                 hand[1]->GetRank() == 7 &&
                 hand[2]->GetRank() == 7)
        {
            if (hand[0]->GetSuit() == hand[1]->GetSuit() &&
                hand[0]->GetSuit() == hand[2]->GetSuit())
            {
                // We have suited 7s, lets payout appropraitely. Spades 3:1, other suits 2:1
                //
                if (hand[0]->GetSuit() == static_cast<int>(TSuitType::SPADES))
                {
                    if (DEBUG) {std::cout << "Player[" << playerIndex << "] sees WIN_SP7." << std::endl;}
                    ret = Sim::FACTOR_WIN_SP7;
                }
                else
                {
                    if (DEBUG) {std::cout << "Player[" << playerIndex << "] sees WIN_S7." << std::endl;}
                    ret = Sim::FACTOR_WIN_S7;
                }
            }
            else
            {
                // Off-suit pays 3:2
                if (DEBUG) {std::cout << "Player[" << playerIndex << "] sees WIN_7." << std::endl;}
                ret = Sim::FACTOR_WIN_7;
            }
        }
        else if (hand.size() == 3 &&
                 Is678(hand[0]->GetRank(), hand[1]->GetRank(), hand[2]->GetRank()))
        {
            // 6 7 8 bonus
            //
            if (hand[0]->GetSuit() == hand[1]->GetSuit() &&
                hand[0]->GetSuit() == hand[2]->GetSuit())
            {
                // We have suited 678, lets payout appropraitely. Spades 3:1, other suits 2:1
                //
                if (hand[0]->GetSuit() == static_cast<int>(TSuitType::SPADES))
                {
                    if (DEBUG) {std::cout << "Player[" << playerIndex << "] sees WIN_SP678." << std::endl;}
                    ret = Sim::FACTOR_WIN_SP678;
                }
                else
                {
                    if (DEBUG) {std::cout << "Player[" << playerIndex << "] sees WIN_S678." << std::endl;}
                    ret = Sim::FACTOR_WIN_S678;
                }
            }
            else
            {
                // Off-suit pays 3:2
                if (DEBUG) {std::cout << "Player[" << playerIndex << "] sees WIN_678." << std::endl;}
                ret = Sim::FACTOR_WIN_678;
            }
        }
        else
        {
            int numCards = _playersVec[playerIndex]->_hands[handIndex].size();
            if (numCards == 5)
            {
                if (DEBUG) {std::cout << "Player[" << playerIndex << "] sees WIN_5_CARD_BONUS." << std::endl;}
                ret = Sim::FACTOR_WIN_5_CARD_BONUS;
            }
            else if (numCards == 6)
            {
                if (DEBUG) {std::cout << "Player[" << playerIndex << "] sees WIN_6_CARD_BONUS." << std::endl;}
                ret = Sim::FACTOR_WIN_6_CARD_BONUS;
            }
            else if (numCards >= 7)
            {
                if (DEBUG) {std::cout << "Player[" << playerIndex << "] sees WIN_7_CARD_BONUS." << std::endl;}
                ret = Sim::FACTOR_WIN_7_CARD_BONUS;
            }
            else
            {
                if (DEBUG) {std::cout << "Player[" << playerIndex << "] sees WIN." << std::endl;}
                ret = Sim::FACTOR_WIN;
            }
        }
    }

    return ret;
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
 * This function runs a given player's hands to completion.  If
 * the player splits off multiple hands, then this function
 * recurses for that player in order to complete all of their hands.
 *
 */
void Sim::PlayHand(int pIdx, int hIdx)
{
    auto& player = _playersVec[pIdx];

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
                if(DEBUG) {std::cout << "Single ace sees a natural." << std::endl;}
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
        auto decision = GetDecision(player, player->_hands[hIdx], hIdx);
        if (DEBUG) {std::cout << "Decision: "; PrintDecision(decision);}

        // CHECK AND HANDLE Split action
        if (decision == TPlayAction::SPLIT)
        {
            if (DEBUG) {std::cout << "Handling split action." << std::endl;}
            player->_hands.push_back(std::vector<std::unique_ptr<Card> >());
            player->_activeVec.push_back(true);
            player->_doubleVec.push_back(0);

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
        // CHECK AND HANDLE Double action
        else if (decision == TPlayAction::DOUBLE)
        {
            if (DEBUG) {std::cout << "Handling double action." << std::endl;}
            { 
                player->_hands[hIdx].push_back(GetGame()->DealCard());
                player->_doubleVec[hIdx] += 1;
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

                //
                // We are finished with this hand if we reach the maximum number
                // of doubles, but we may have further decisions if the rules
                // allow it
                //
                if (player->NumDoubles(hIdx) >= GetGame()->GetNumDoubles())
                {
                    break;
                }
            }
        }
        // CHECK AND HANDLE Stand action
        else if (decision == TPlayAction::STAND)
        {
            //
            // The stand action has been verified by this point
            //
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
            if (DEBUG) {std::cout << "Handling surrender action." << std::endl;}
            PayoutPlayer(player, hIdx, Sim::FACTOR_SURRENDER);
            player->_activeVec[hIdx] = false;
            break;
        }
        // Should never happen
        else
        {
            std::cerr << "ERROR: Unknown action!" << std::endl;
            exit(-1);
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
