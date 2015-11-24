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
    std::vector<Bet> &GetBetVec(){ return _betVec; }
    std::vector< std::vector<std::unique_ptr<Card> > > &GetHands(){ return _hands; }
    std::vector<std::unique_ptr<Card> > &GetHand(int i){ return _hands[i]; }

    void ResetPlayer();
    void SetInitialBet(Game * game);

    Player();
    ~Player()
    {
        std::cout << "Player dtor." << std::endl;
    }

private:
    int _chips;
    std::vector<Bet> _betVec;
    std::vector< std::vector<std::unique_ptr<Card> > > _hands;

};

#endif
