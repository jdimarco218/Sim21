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
    // Payout coefficients, these include the original amount
    static constexpr double FACTOR_BLACKJACK = 2.5;
    static constexpr double FACTOR_WIN       = 2.0;
    static constexpr double FACTOR_PUSH      = 1.0;
    static constexpr double FACTOR_SURRENDER = 0.5;
    static constexpr double FACTOR_INSURANCE = 1.5;

    void RunSimulation();
    void RunStrategySimulation();
    void RunEorSimulation();
    void RunIndexSimulation();
    void SimulateHand(Game * game);
    void SaveStatistics();
    bool IsSimulationFinished();
    void PrintGameState(Game * game);
    void CheckInsuranceAndBlackjack();
    bool WantsInsurance(int playerIdx);
    bool IsAceUp();
    int  GetOptimalValue(const std::vector<std::unique_ptr<Card> >& hand);
    void PayoutPlayer(std::unique_ptr<Player>& player, int handIdx, double payoutFactor);
    void PayoutInsurance(std::unique_ptr<Player>& player);
    std::unique_ptr<Player>& GetPlayerAt(int idx);
    std::unique_ptr<Player>& GetDealer(){ return _dealer; }
    std::unique_ptr<Game>&   GetGame(){ return _game; }
    std::vector< std::unique_ptr<Player> >& GetPlayersVec(){ return _playersVec; }

    Sim(TSimMode simMode, TDeckType deckType);
    ~Sim()
    {
        //std::cout << "Sim dtor." << std::endl;
    }

private:
    std::unique_ptr<Game>                        _game;
    std::unique_ptr<Player>                    _dealer;
    std::vector< std::unique_ptr<Player> > _playersVec;
    int                                   _handsPlayed;
    int                                   _handsToPlay;
    TSimMode                                  _simMode;
    TDeckType                                _deckType;
    int                                   _upCardIndex;

};

#endif
