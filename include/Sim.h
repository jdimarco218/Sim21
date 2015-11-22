#ifndef SIM_H
#define SIM_H

#include <vector>
#include "Game.h"
#include "Player.h"

// Forward declarations
class Game;

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
    void SimulateHand(Game game);
    void SaveStatistics();
    bool IsSimulationFinished();

    Sim(TSimMode simMode, TDeckType deckType);
    ~Sim();

private:
    std::vector<Player> _playersVec;
    int _handsPlayed;
    int _handsToPlay;
    TSimMode _simMode;
    TDeckType _deckType;

};

#endif
