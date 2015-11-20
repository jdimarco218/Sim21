#ifndef DECK_H
#define DECK_H

#include <list>
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
    std::list<Card> GetCards(){ return _cards; }

    Deck(TDeckType deckType); 
    ~Deck(){};

private:
    std::list<Card> _cards;

};

#endif

