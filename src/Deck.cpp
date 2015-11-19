#include "Card.h"
#include "Deck.h"

Deck::Deck(TDeckType deckType)
{
    switch(deckType)
    {
        case TDeckType::BLACKJACK:
            break;
        case TDeckType::SPANISH21:
            break;
        default:
            break;
    }
}

