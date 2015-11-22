#ifndef SIM_H
#define SIM_H

#include "Game.h"

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
    void SaveStatistics();
    bool IsSimulationFinished();

    Sim(TSimMode simMode, TDeckType deckType);
    ~Sim();

private:
    int _handsPlayed;
    TSimMode _simMode;
    TDeckType _deckType;

};

#endif
