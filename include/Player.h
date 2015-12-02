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
    std::vector<Bet> &GetBetVec(){ return _handsBetVec; }
    std::vector< std::vector<std::unique_ptr<Card> > > &GetHands(){ return _hands; }
    std::vector<std::unique_ptr<Card> > &GetHand(int i){ return _hands[i]; }

    void ResetPlayer();
    void SetInitialBet(Game * game);
    void MakeAdditionalBet(int handIdx, int betAmount);
    void MakeInsuranceBet();

    Player();
    ~Player()
    {
        //std::cout << "Player dtor." << std::endl;
    }

private:
    bool _active;
    int _chips;
    std::vector<Bet> _handsBetVec;
    std::unique_ptr<Bet> _insuranceBet;
    std::vector< std::vector<std::unique_ptr<Card> > > _hands;
    long int _totalWagered;
    long int _totalWinnings;

};

#endif
