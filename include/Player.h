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

using std::map;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;

enum class TPlayAction
{
    NONE = -1,
    STAND = 0,
    HIT = 1,
    DOUBLE = 2,
    SPLIT = 3,
    SURRENDER = 4
};

class Player
{

public:
    friend class Sim;

    static map<string, vector<pair<TPlayAction, TPlayAction> > > bs_s17_das_ls;
    static map<string, vector<pair<TPlayAction, TPlayAction> > > bs_h17_das_ls;
    static map<string, vector<pair<TPlayAction, TPlayAction> > > bs_s17_das_ns;
    static map<string, vector<pair<TPlayAction, TPlayAction> > > bs_h17_das_ns;
    map<string, vector<pair<TPlayAction, TPlayAction> > > GetMap();

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
    double GetChips(){ return _chips; }
    void SetChips(double chips){ _chips = chips; }

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
    std::vector<bool>                              _activeVec;
    std::vector<bool>                              _doubleVec;
    std::vector<std::unique_ptr<Bet> >           _handsBetVec;
    std::unique_ptr<Bet>                        _insuranceBet;
    std::vector< std::vector<std::unique_ptr<Card> > > _hands;

};

#endif
