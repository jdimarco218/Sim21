#ifndef SIM_H
#define SIM_H

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "Game.h"
#include "Player.h"

using std::map;
using std::pair;
using std::string;
using std::vector;

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
    static constexpr double FACTOR_BLACKJACK        = 2.5;
    static constexpr double FACTOR_WIN              = 2.0;
    static constexpr double FACTOR_WIN_5_CARD_BONUS = 2.5;
    static constexpr double FACTOR_WIN_6_CARD_BONUS = 3.0;
    static constexpr double FACTOR_WIN_7_CARD_BONUS = 4.0;
    static constexpr double FACTOR_PUSH             = 1.0;
    static constexpr double FACTOR_SURRENDER        = 0.5;
    static constexpr double FACTOR_INSURANCE        = 1.5;
    // In the very rare case of a super bonus, we calculate
    // the factor at the time of payout. The result should be
    // 1000 total for bet amounts of 5-24, and 5000 for bet
    // amounts of at least 25.

    void RunSimulation();
    void RunStrategySimulation();
    void RunEorSimulation();
    void RunIndexSimulation();
    void SimulateHand(Game * game);
    bool IsSimulationFinished();
    void PrintGameState(Game * game);
    void PrintDecision(TPlayAction action);
    void PrintChips();
    void CheckInsuranceAndBlackjack();
    bool WantsInsurance(int playerIdx);
    bool IsAceUp();
    bool CanTakeAction(std::unique_ptr<Player>& player, std::vector<std::unique_ptr<Card> >& hand, int hIdx, TPlayAction action);
    int  GetOptimalValue(const std::vector<std::unique_ptr<Card> >& hand) const;
    int  GetMinimalValue(const std::vector<std::unique_ptr<Card> >& hand) const;
    std::string GetStratKey(const std::vector<std::unique_ptr<Card> >& hand, bool hardTotal = false) const;
    int GetUpCardRank();
    int GetUpCardSuit();
    bool IsHandSoft(const std::vector<std::unique_ptr<Card> >& hand) const;
    bool IsBlackjack(const std::vector<std::unique_ptr<Card> >& hand) const;
    bool IsTwoOf678(int r0, int r1);
    bool IsDoubleAction(TPlayAction action);
    void PayoutPlayer(std::unique_ptr<Player>& player, int handIdx, double payoutFactor);
    void PayoutInsurance(std::unique_ptr<Player>& player);
    void PlayHand(int pIdx, int hIdx);
    void PlayDealerHand();
    void PayoutWinners();
    void SaveStatistics();
    void FinalizeStatistics();
    std::unique_ptr<Player>& GetPlayerAt(int idx);
    std::unique_ptr<Player>& GetDealer(){ return _dealer; }
    std::unique_ptr<Game>&   GetGame(){ return _game; }
    std::vector< std::unique_ptr<Player> >& GetPlayersVec(){ return _playersVec; }
    TPlayAction GetDecision(std::unique_ptr<Player>& player, std::vector<std::unique_ptr<Card> >& hand, int hIdx);
    double CheckForBonusPayout(int playerIndex, int handIndex);

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
    int                                   _shoesPlayed;
    int                                   _handsToPlay;
    TSimMode                                  _simMode;
    TDeckType                                _deckType;
    int                                   _upCardIndex;
    std::string                             _outputDir;
    std::vector<std::string>              _playerNames;
    int                              _saveStatsPerShoe;

};

#endif
