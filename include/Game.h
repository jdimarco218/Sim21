#ifndef GAME_H
#define GAME_H

#include <list>
#include <vector>
#include "Card.h"
#include "Deck.h"
#include "Shoe.h"

/**
 * The Game class holds the current game state of everything that
 * is detached from the simulation. It is like the table at a casino
 * in that it contains the cards of the current game, the penetration
 * and cut card, the number of decks, and the current count(s).
 */
class Game
{
public:
    int GetCutCardPosition(){ return _cutCardPosition; }
    std::list<Card> GetCards(){ return _shoe.GetCards(); }
    Card DealCard();

    Game();
    Game(TDeckType deckType, int numDecks = 6, int cutPercentMin = 75, int cutPercentMax = 80);

private:
    Shoe _shoe;
    // TODO count stuffs
    int _cutCardPosition;
    int _hiloCount;
    

};

#endif
