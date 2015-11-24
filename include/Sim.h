#ifndef SIM_H
#define SIM_H

#include <iostream>
#include <memory>
#include <vector>
#include "Game.h"
#include "Player.h"

enum class TSimMode
{
    STRATEGY = 0,
    EOR = 1,
    INDEX = 2    
};

class Sim
{
public:
    void RunSimulation();
    void RunStrategySimulation();
    void RunEorSimulation();
    void RunIndexSimulation();
    void SimulateHand(Game &game);
    void SaveStatistics();
    bool IsSimulationFinished();
    void PrintGameState(Game &game);

    Sim(TSimMode simMode, TDeckType deckType);
    ~Sim()
    {
        std::cout << "Sim dtor." << std::endl;
    }

private:
    std::unique_ptr<Player> _dealer;
    std::vector< std::unique_ptr<Player> > _playersVec;
    int _handsPlayed;
    int _handsToPlay;
    TSimMode _simMode;
    TDeckType _deckType;

};

#endif
