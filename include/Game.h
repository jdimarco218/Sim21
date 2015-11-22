#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Deck.h"
#include "Sim.h"
#include "Player.h"
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
    Game(TDeckType deckType, int numDecks, int cutPercentMin, int cutPercentMax);

private:
    Shoe _shoe;
    // TODO count stuffs
    int _cutCardPosition;
    int _hiloCount;
    

};

#endif
