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
        player->_hands[0].emplace_back(game->DealCard());
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
    auto insuranceList = std::list<Player>();

    if (isAceUp)
    {
        for (int i = 0; i < _playersVec.size(); ++i)
        {
            if (WantsInsurance(i))
            {
            }
        }
    }

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
