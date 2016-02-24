#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "Bet.h"
#include "Card.h"
#include "Game.h"
#include "Strategy.h"

using std::map;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;

enum class TPlayAction
{
    NONE,
    STAND,
    HIT,
    DOUBLE,
    SPLIT,
    SURRENDER,

    // Spanish 21 unique actions
    STAND_X_4,
    STAND_X_5,
    STAND_X_6,
    SPLIT_X_S7,
    DOUBLE_X_3,
    DOUBLE_X_4,
    DOUBLE_X_5,
    DOUBLE_X_6,
    HIT_IF_678,
    HIT_IF_S678,
    HIT_IF_SP678,
    HIT_IF_SUPER
};

class Player
{

public:
    friend class Sim;

    static map<string, vector<pair<TPlayAction, TPlayAction> > > bs_s17_das_ls;
    static map<string, vector<pair<int, pair<TPlayAction, TPlayAction> > > > ds_s17_das_ls;
    static map<string, vector<pair<TPlayAction, TPlayAction> > > bs_sp_h17;
    //static map<string, vector<pair<TPlayAction, TPlayAction> > > bs_h17_das_ls;
    //static map<string, vector<pair<TPlayAction, TPlayAction> > > bs_s17_das_ns;
    //static map<string, vector<pair<TPlayAction, TPlayAction> > > bs_h17_das_ns;
    map<string, vector<pair<TPlayAction, TPlayAction> > > GetPlayStrategy(std::unique_ptr<Game>& game);
    map<string, vector<pair<int, pair<TPlayAction, TPlayAction> > > > GetDeviationStrategy();

    std::vector<std::unique_ptr<Bet> > &GetBetVec(){ return _handsBetVec; }
    std::vector<std::vector<std::unique_ptr<Card> > > &GetHands(){ return _hands; }
    std::vector<std::unique_ptr<Card> > &GetHand(int i){ return _hands[i]; }

    void ResetPlayer();
    void SetInitialBet(Game * game);
    void SetWantsInsurance(bool wantsInsurance);
    void MakeAdditionalBet(int handIdx, int betAmount);
    double GetHandBetAmount(int handIdx); 
    void MakeInsuranceBet();
    bool WantsInsurance(Game * game);
    inline int  NumHands(){ return _hands.size(); }
    inline double GetChips(){ return _chips; }
    inline int  NumDoubles(int hIdx){ return _doubleVec[hIdx]; }
    inline bool IsCounting(){ return _isCounting; }
    inline bool IsDeviating(){ return _isDeviating; }
    void SetCounting(bool counting);
    void SetDeviating(bool deviating);
    void SetChips(double chips){ _chips = chips; }
    inline bool IsActiveAt(int hIdx){ return _activeVec[hIdx]; }

    Player();
    ~Player()
    {
        //std::cout << "Player dtor." << std::endl;
    }

private:
    double                                             _chips;
    long double                                 _totalWagered;
    long double                                _totalWinnings;
    bool                                      _wantsInsurance;
    bool                                          _isCounting;
    bool                                         _isDeviating;
    int                                           _numDoubles;
    std::unique_ptr<Strategy>                       _strategy;
    std::vector<bool>                              _activeVec;
    std::vector<int>                               _doubleVec;
    std::vector<std::unique_ptr<Bet> >           _handsBetVec;
    std::unique_ptr<Bet>                        _insuranceBet;
    std::vector< std::vector<std::unique_ptr<Card> > > _hands;

};

#endif
