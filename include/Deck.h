#ifndef DECK_H
#define DECK_H

#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <vector>
#include "Card.h"

enum class TDeckType
{
    BLACKJACK = 0,
    SPANISH21 = 1

};

class Deck
{
    friend class Shoe;
public:

    Deck()
    {
        _cards = std::deque<std::unique_ptr<Card> >();
    }
    Deck(TDeckType deckType); 
    ~Deck()
    {
        //std::cout << "Deck dtor." << std::endl;
    }

protected:
    std::deque<std::unique_ptr<Card> > _cards;

};

#endif

