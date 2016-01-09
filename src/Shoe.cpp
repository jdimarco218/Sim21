#include <algorithm>
#include <deque>
#include <list>
#include <memory>
#include <random>
#include <unistd.h>
#include <vector>
#include "Shoe.h"
#include "Deck.h"

Shoe::Shoe(int numDecks, TDeckType deckType)
{
    for(int i = 0; i < numDecks; ++i)
    {
        std::unique_ptr<Deck> deck(std::unique_ptr<Deck>(new Deck(deckType)));

        for (auto& card : deck->_cards)
        {
            _shoeCards.push_back(std::move(card));
        }
    }
    _numDecks = numDecks;
    switch (deckType)
    {
        case TDeckType::BLACKJACK:
            _cardsPerDeck = 52;
        case TDeckType::SPANISH21:
            _cardsPerDeck = 48;
        default:
            _cardsPerDeck = 52;
    }
}

void Shoe::ShuffleCards()
{
    std::mt19937 r{std::random_device{}()};
    std::shuffle(std::begin(_shoeCards), std::end(_shoeCards), r);
    //srand(Mix(clock(), time(0), getpid()));
    //std::random_shuffle(_shoeCards.begin(), _shoeCards.end());

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

double Shoe::GetNumDecksRemaining()
{
    return static_cast<double>(_shoeCards.size()) / 
           static_cast<double>(_cardsPerDeck);
}

int Shoe::GetNumStartingCards()
{
    return _cardsPerDeck * _numDecks;
}
