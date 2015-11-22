#include <iostream>
#include <list>
#include <vector>
#include "Sim.h"
#include "Deck.h"
#include "Player.h"

Sim::Sim(TSimMode simMode, TDeckType deckType)
{
    int numPlayers = 2;
    for(int i = 0; i < numPlayers; ++i)
    {
        _playersVec.push_back(Player());
    }
    _handsPlayed = 0;
    _handsToPlay = 3;
    _simMode = simMode;
    _deckType = deckType;
}

Sim::~Sim()
{
    // dtor
    return;
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
    Game currGame = Game(_deckType);

    std::cout << "Cut card: " << currGame.GetCutCardPosition() << " out of " << currGame.GetCards().size() << std::endl;

    while(!IsSimulationFinished())
    {
        std::cout << "Playing hand..." << std::endl;
        SimulateHand(currGame);
        _handsPlayed++;
    }
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

void Sim::SimulateHand(Game game)
{
    std::cout << "Starting a new hand..." << std::endl;

    // Get bets and reset players
    for(auto &player : _playersVec)
    {
        player.ResetPlayer();
        player.SetInitialBet(game);
    }

    // Deal all initial cards
    std::cout << "Dealing cards." << std::endl;
    for(auto &player : _playersVec)
    {
        //Card card = game.DealCard();
        Card card(game.DealCard());
        std::cout << "Dealing " << card << std::endl;
        player._hands[0].push_back(card);
        std::cout << "Hand[0].size(): " << player._hands[0].size() << std::endl;
        for(auto card : player._hands[0])
        {
            std::cout << card << ", ";
        }
    }

    std::cout << "Printing game state." << std::endl;
    PrintGameState(game);

    // Check insurance, bonuses, sidebets, and blackjack

    // Play each player's hand

    // Play dealer's hand

    // Payouts

    return;
}

void Sim::PrintGameState(Game game)
{
    for(auto player : _playersVec)
    {
        std::cout << "Player hand: ";
        for(auto hand : player.GetHands())
        {
            for(auto card : hand)
            {
                std::cout << card << ", ";
            }
            std::cout << std::endl;
        }
    }

    return;
}
