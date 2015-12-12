#ifndef BET_H
#define BET_H

#include <iostream>

class Bet
{
    friend class Sim;
    friend class Player;
public:
    inline double    GetAmount(){ return _amount; }
    inline double GetPayout(){ return _payout; }
    Bet(){}
    Bet(double amount) : _amount(amount) {}
    Bet(double amount, double payout);
    ~Bet()
    {
        //std::cout << "Bet dtor." << std::endl;
    }

private:
    double _amount;
    double _payout;

};

#endif
