#ifndef SHOE_H
#define SHOE_H

#include <list>
#include <vector>
#include "Card.h"
#include "Deck.h"

class Shoe
{
public:
    inline std::list<Card> GetCards(){ return _shoeCards; }
    Shoe(){};
    Shoe(int numDecks, TDeckType deckType);
    ~Shoe(){}

private:
    int              _numDecks;
    int        _cardsRemaining;
    std::list<Card> _shoeCards; 

};

#endif
