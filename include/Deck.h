#ifndef DECK_H
#define DECK_H

#include <vector>
#include "Card.h"

typedef enum TDeckType
{
    BLACKJACK = 0,
    SPANISH21 = 1

} TDeckType;

class Deck
{
public:
    Deck(TDeckType deckType); 
    ~Deck(){};

private:
    std::vector<Card> _cards;

};

#endif

