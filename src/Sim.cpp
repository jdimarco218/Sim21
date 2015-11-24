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
        //Card card0(game.DealCard());
        //Card card1(game.DealCard());
        std::cout << "Hand[0].size(): " << player->_hands[0].size() << std::endl;
        std::cout << "Dealing to a player now." << std::endl;
        player->_hands[0].push_back(game->DealCard());
        std::cout << "Dealing to a player now." << std::endl;
        player->_hands[0].push_back(game->DealCard());
        //player->_hands[0].push_back(game.DealCard());
        std::cout << "Hand[0].size(): " << player->_hands[0].size() << std::endl;
    }
    // Dealer's initial cards
    _dealer->_hands[0].push_back(game->DealCard());
    _dealer->_hands[0].push_back(game->DealCard());

    std::cout << "Printing game state." << std::endl;
    PrintGameState(game);

    // Check insurance, bonuses, sidebets, and blackjack
    //

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
    //for(auto& player : _playersVec)
    //{
    //    std::cout << "Player hand: ";
    //    for(auto& hand : player->_hands)
    //    {
    //        for(auto& card : hand)
    //        {
    //            //std::cout << *card << ", ";
    //        }
    //        std::cout << std::endl;
    //    }
    //}

    return;
}
