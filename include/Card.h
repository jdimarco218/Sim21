#ifndef CARD_H
#define CARD_H

enum class TSuitType
{
    CLUBS = 0,
    DIAMONDS = 1,
    HEARTS = 2,
    SPADES = 3
};

class Card
{
public:
    inline int GetRank(){ return _rank; }
    inline int GetSuit(){ return _suit; }

    Card(int rank, int suit);
    ~Card(){};

private:
    int _rank;
    int _suit;

};

#endif

