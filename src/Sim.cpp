#include <assert.h>
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
    _handsToPlay = 3;
    _simMode = simMode;
    _deckType = deckType;
    _upCardIndex = 0;
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
    std::cout << "RunStrategySimulation()..." << std::endl;

    // Start a new Game
    //std::unique_ptr<Game> currGame(new Game(_deckType));
    //_game = new Game(_deckType);
    //_game(std::unique_ptr<Game>(new Game(_deckType)));
    _game->ResetGame();

    std::cout << "Cut card: " << _game->GetCutCardPosition() << " out of " << _game->GetCardsRemaining() << std::endl;

    while(!IsSimulationFinished())
    {
        std::cout << "Playing hand..." << std::endl;
        SimulateHand(_game.get());
        _handsPlayed++;
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

void Sim::SimulateHand(Game * game)
{
    std::cout << "Starting a new hand..." << std::endl;

    // Get bets and reset players
    //
    for(auto& player : _playersVec)
    {
        player->ResetPlayer();
        player->SetInitialBet(game);
    }

    // Deal all initial cards
    //
    std::cout << "Dealing cards." << std::endl;
    for(auto& player : _playersVec)
    {
        // Deal two cards
        player->_hands[0].push_back(game->DealCard());
        player->_hands[0].push_back(game->DealCard());
    }
    // Dealer's initial cards
    _dealer->_hands[0].push_back(game->DealCard());
    _dealer->_hands[0].push_back(game->DealCard());

    std::cout << std::endl;
    std::cout << "Printing game state." << std::endl;
    PrintGameState(game);
    std::cout << std::endl;

    // Check insurance, bonuses, sidebets, and blackjack
    //
    CheckInsuranceAndBlackjack();

    // Play each player's hand
    //
    for (int i = 0; i < _playersVec.size(); ++i)
    {
        std::cout << "Playing player " << i << "'s hand(s)..." << std::endl;
        PlayHand(i, 0);
    }

    // Play dealer's hand
    //

    // Payouts
    //

    return;
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

    return;
}

void Sim::CheckInsuranceAndBlackjack()
{
    bool isAceUp = IsAceUp();

    //if(DEBUG){ std::cout << "db. IsAceUp(): " << isAceUp << std::endl; }

    // First handle insurance if an ace is showing
    for (auto& player : _playersVec)
    {
        if ( isAceUp && player->WantsInsurance(_game.get()) )
        {
            if(DEBUG){ std::cout << "db.   Player takes insurance." << std::endl; }
            player->MakeInsuranceBet();
        }

    }

    // Handle dealer's blackjack
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

                if(DEBUG){ std::cout << "db.   Player has bj." << std::endl; }
                PayoutPlayer(player, 0, Sim::FACTOR_PUSH);
            }
            else
            {
                if(DEBUG){ std::cout << "db.   Player does not have bj." << std::endl; }
                // Player doesn't have blackjack but dealer does
            }
        }
    }
    else // Dealer does NOT have blackjack
    { 
        if(DEBUG){ std::cout << "db.   Dealer does not have bj." << std::endl; }
        for (auto &player : _playersVec)
        {
            if (player->_hands[0].size() == 2 && GetOptimalValue(player->_hands[0]) == 21)
            {
                PayoutPlayer(player, 0, Sim::FACTOR_BLACKJACK);
                player->_active = false;
            }
        }
    }

    return;
}

/**
 * This function returns the lowest rank possible that is <= 21.
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
 * Aces can be 1 or 11, and all face cards are 10
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

void Sim::PlayHand(int pIdx, int hIdx)
{
    auto& player = _playersVec[pIdx];
    auto& hand = player->GetHand(hIdx);
    while (GetOptimalValue(hand) < 21)
    {
        // Deal first card if this is a hand resulting from a split (one card)
        if (hand.size() == 1)
        {
            //TODO
        }

        // CHECK AND HANDLE Split action
        //if (GetDecision(
    }

    return;
}

std::string Sim::GetStratKey(const std::vector<std::unique_ptr<Card> >& hand)
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
        return "p" + std::to_string(rank_0);
    }
    else if (IsHandSoft(hand))
    {
        return "s" + std::to_string(GetOptimalValue(hand)); 
    }
    
    return std::to_string(GetOptimalValue(hand));
}

TPlayAction GetDecision(std::vector<std::unique_ptr<Card> >& hand, Game * game)
{
    return TPlayAction::NONE;
}

bool Sim::IsHandSoft(const std::vector<std::unique_ptr<Card> >& hand) const
{
    return GetOptimalValue(hand) != GetMinimalValue(hand);
}
