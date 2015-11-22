#ifndef PLAYER_H
#define PLAYER_H

#include <list>
#include <vector>
#include "Bet.h"
#include "Card.h"

class Player
{
public:
    std::vector<Bet> GetBetVec(){ return _betVec; }
    std::vector< std::vector<Card> > GetHands(){ return _hands; }
    std::vector<Card> GetHand(int i){ return _hands[i]; }
    void ResetPlayer();

    Player();
    ~Player(){}

private:
    int _chips;
    std::vector<Bet> _betVec;
    std::vector< std::vector<Card> > _hands;

};

#endif
