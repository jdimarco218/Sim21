#ifndef BET_H
#define BET_H

class Bet
{
public:
    inline int    GetAmount(){ return _amount; }
    inline double GetPayout(){ return _payout; }
    Bet(int amount, double payout);
    ~Bet(){};

private:
    int _amount;
    double _payout;

};

#endif
