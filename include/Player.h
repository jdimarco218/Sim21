#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <list>
#include <memory>
#include <vector>
#include "Bet.h"
#include "Card.h"
#include "Game.h"

class Player
{

public:
    friend class Sim;
    std::vector<std::unique_ptr<Bet> > &GetBetVec(){ return _handsBetVec; }
    std::vector<std::vector<std::unique_ptr<Card> > > &GetHands(){ return _hands; }
    std::vector<std::unique_ptr<Card> > &GetHand(int i){ return _hands[i]; }

    void ResetPlayer();
    void SetInitialBet(Game * game);
    void SetWantsInsurance(bool wantsInsurance);
    void MakeAdditionalBet(int handIdx, int betAmount);
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
    bool _active;
    double _chips;
    std::vector<std::unique_ptr<Bet> > _handsBetVec;
    std::unique_ptr<Bet> _insuranceBet;
    std::vector< std::vector<std::unique_ptr<Card> > > _hands;
    long int _totalWagered;
    long int _totalWinnings;
    bool _wantsInsurance;

};

#endif
