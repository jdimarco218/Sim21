#ifndef DECK_H
#define DECK_H

#include <vector>
#include "Card.h"

enum class TDeckType
{
    BLACKJACK = 0,
    SPANISH21 = 1

};

class Deck
{
public:
    Deck(TDeckType deckType); 
    ~Deck(){};

private:
    std::vector<Card> _cards;

};

#endif

