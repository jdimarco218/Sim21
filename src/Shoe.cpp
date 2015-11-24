#include "Shoe.h"
#include "Deck.h"

Shoe::Shoe(int numDecks, TDeckType deckType)
{
    for(int i = 0; i < numDecks; ++i)
    {
        _shoeCards.splice(_shoeCards.end(), Deck(deckType).GetCards());
    }
    _numDecks = numDecks;
    _cardsRemaining = _shoeCards.size();
}
