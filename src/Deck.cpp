#include <memory>
#include "Card.h"
#include "Deck.h"

Deck::Deck(TDeckType deckType)
{
    switch(deckType)
    {
        case TDeckType::BLACKJACK:
            for(int i = 0; i < 4; ++i)
            {
                for(int j = 1; j < 13; ++j)
                {
                    _cards.push_back(std::unique_ptr<Card>(new Card(i, j)));
                }
            }
            break;
        case TDeckType::SPANISH21:
            for(int i = 0; i < 4; ++i)
            {
                for(int j = 1; j < 14; ++j)
                {
                    if(j != 10)
                    {
                        _cards.push_back(std::unique_ptr<Card>(new Card(i, j)));
                    }
                }
            }
            break;
        default:
            break;
    }
}

