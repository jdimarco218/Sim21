#ifndef BET_H
#define BET_H

#include <iostream>

class Bet
{
    friend class Sim;
    friend class Player;
public:
    inline int    GetAmount(){ return _amount; }
    inline double GetPayout(){ return _payout; }
    Bet(){}
    Bet(int amount) : _amount(amount) {}
    Bet(int amount, double payout);
    ~Bet()
    {
        //std::cout << "Bet dtor." << std::endl;
    }

private:
    int _amount;
    double _payout;

};

#endif
