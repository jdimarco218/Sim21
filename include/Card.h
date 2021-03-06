#ifndef CARD_H
#define CARD_H

#include <iostream>

enum class TSuitType : int
{
    CLUBS = 0,
    DIAMONDS = 1,
    HEARTS = 2,
    SPADES = 3
};

enum class TRankType
{
    ACE = 1,
    TWO = 2,
    THREE = 3,
    FOUR = 4,
    FIVE = 5,
    SIX = 6,
    SEVEN = 7,
    EIGHT = 8,
    NINE = 9,
    TEN = 10,
    JACK = 11,
    QUEEN = 12,
    KING = 13
};

class Card
{
public:
    inline int GetRank() const { return _rank; }
    inline int GetSuit() const { return _suit; }

    friend std::ostream& operator<<(std::ostream& os, Card &card)
    {
        os << card._rank << "." << card._suit;
        return os;
    }

    Card()
    {
        _rank = 1;
        _suit = 0;
    }
    Card(int rank, int suit);
    ~Card()
    {
        //std::cout << "Card dtor." << std::endl;
    }

private:
    int _rank;
    int _suit;

};

#endif
