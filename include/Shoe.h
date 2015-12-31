#ifndef SHOE_H
#define SHOE_H

#include <deque>
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
    inline std::deque<std::unique_ptr<Card> > &GetCards(){ return _shoeCards; }
    inline int GetCardsRemaining(){ return _shoeCards.size(); }
    inline bool IsEmpty(){ return _shoeCards.size() == 0; }
    void ShuffleCards();
    unsigned long Mix(unsigned long a, unsigned long b, unsigned long c);

    Shoe()
    {
        _numDecks = 0;
        _shoeCards = std::deque<std::unique_ptr<Card> >();
    }
    Shoe(int numDecks, TDeckType deckType);
    ~Shoe()
    {
        //std::cout << "Shoe dtor." << std::endl;
    }

private:
    int                                  _numDecks;
    std::deque<std::unique_ptr<Card> > _shoeCards; 

};

#endif
