#ifndef CARD_H
#define CARD_H

class Card
{
public:
    int getRank(){ return _rank; }
    int getSuit(){ return _suit; }

    Card(int rank, int suit);
    ~Card(){};

private:
    int _rank;
    int _suit;

};

#endif
