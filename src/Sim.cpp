#include <iostream>
#include <list>
#include <memory>
#include <vector>
#include "Sim.h"
#include "Deck.h"
#include "Player.h"

Sim::Sim(TSimMode simMode, TDeckType deckType)
{
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
    std::unique_ptr<Game> currGame(new Game(_deckType));

    std::cout << "Cut card: " << currGame->GetCutCardPosition() << " out of " << currGame->GetCardsRemaining() << std::endl;

    while(!IsSimulationFinished())
    {
        std::cout << "Playing hand..." << std::endl;
        SimulateHand(currGame.get());
        _handsPlayed++;
    }

    //delete currGame;
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
    CheckInsuranceAndBlackjack(game);

    // Play each player's hand
    //

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

void Sim::CheckInsuranceAndBlackjack(Game * game)
{
    bool isAceUp = IsAceUp();

    // Handle dealer's blackjack
    if (_dealer->_hands[0].size() == 2 && GetOptimalValue(_dealer->_hands[0]) == 21)
    {
        for (auto &player : _playersVec)
        {
            if (player->_hands[0].size() == 2 && GetOptimalValue(player->_hands[0]) == 21)
            {
                // Player and dealer both have blackjack
                PayoutPlayer(player, 0, Sim::FACTOR_PUSH);
            }
            // Check for insurance
            if ( isAceUp && player->WantsInsurance(game) )
            {
                PayoutPlayer(player, 0, Sim::FACTOR_PUSH);
            }
        }
    }
    else // Dealer does NOT have blackjack
    { 
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
 * This function returns the best rank possible that is <= 21.
 * Aces can be 1 or 11, and all face cards are 10
 */
int Sim::GetOptimalValue(const std::vector<std::unique_ptr<Card> >& hand)
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
