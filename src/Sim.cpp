#include <list>
#include <vector>
#include "Sim.h"

Sim::Sim(TSimMode simMode, TDeckType deckType)
{
    _handsPlayed = 0;
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
    // Start a new Game
    //SetGame(Game(_deckType));

    while(!IsSimulationFinished())
    {

    }
}

bool Sim::IsSimulationFinished()
{
    return true;
}
