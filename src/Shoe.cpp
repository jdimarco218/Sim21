#include <algorithm>
#include <deque>
#include <list>
#include <memory>
#include <vector>
#include "Shoe.h"
#include "Deck.h"

Shoe::Shoe(int numDecks, TDeckType deckType)
{
    for(int i = 0; i < numDecks; ++i)
    {
        //_shoeCards.splice(_shoeCards.end(), Deck(deckType).GetCards());
        Deck deck = Deck(deckType);
        //_shoeCards.insert(_shoeCards.end(), deck.GetCards().begin, deck.GetCards().end());
        //std::move(deck.GetCards().begin(), deck.GetCards().end(), std::back_inserter(_shoeCards));
        for (auto& card : deck.GetCards())
        {
            _shoeCards.push_back(std::move(card));
        }
    }
    _numDecks = numDecks;
}

void Shoe::ShuffleCards()
{
    srand(Mix(clock(), time(0), getpid()));
    std::random_shuffle(_shoeCards.begin(), _shoeCards.end());

    return;
}

unsigned long Shoe::Mix(unsigned long a, unsigned long b, unsigned long c)
{
    a=a-b;  a=a-c;  a=a^(c >> 13);
    b=b-c;  b=b-a;  b=b^(a << 8);
    c=c-a;  c=c-b;  c=c^(b >> 13);
    a=a-b;  a=a-c;  a=a^(c >> 12);
    b=b-c;  b=b-a;  b=b^(a << 16);
    c=c-a;  c=c-b;  c=c^(b >> 5);
    a=a-b;  a=a-c;  a=a^(c >> 3);
    b=b-c;  b=b-a;  b=b^(a << 10);
    c=c-a;  c=c-b;  c=c^(b >> 15);
    return c;
}
