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
public:
    inline std::deque<std::unique_ptr<Card> > GetCards(){ return std::move(_cards); }

    Deck(TDeckType deckType); 
    ~Deck()
    {
        //std::cout << "Deck dtor." << std::endl;
    }

private:
    std::deque<std::unique_ptr<Card> > _cards;

};

#endif

