#ifndef SHOE_H
#define SHOE_H

#include <iostream>
#include <list>
#include <memory>
#include <vector>
#include "Card.h"
#include "Deck.h"

class Shoe
{
public:
    friend class Game;
    inline std::list<std::unique_ptr<Card> > &GetCards(){ return _shoeCards; }
    inline int GetCardsRemaining(){ return _cardsRemaining; }
    inline bool IsEmpty(){ return _shoeCards.size() == 0; }

    Shoe()
    {
        _numDecks = 0;
        _cardsRemaining = 0;
        _shoeCards = std::list<std::unique_ptr<Card> >();
    }
    Shoe(int numDecks, TDeckType deckType);
    ~Shoe()
    {
        std::cout << "Shoe dtor." << std::endl;
    }

private:
    int              _numDecks;
    int        _cardsRemaining;
    std::list<std::unique_ptr<Card> > _shoeCards; 

};

#endif
