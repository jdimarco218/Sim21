#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "Card.h"
//#include "Deck.h"
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
    inline int GetCardsRemaining(){ return _shoe.GetCardsRemaining(); }
    std::unique_ptr<Card> DealCard();

    Game()
    {
        _shoe = Shoe();
        _cutCardPosition = 0;
        _hiloCount = 0;
    }
    Game(TDeckType deckType, int numDecks = 6, int cutPercentMin = 75, int cutPercentMax = 80);
    ~Game()
    {
        std::cout << "Game dtor." << std::endl;
    }  

private:
    Shoe _shoe;
    // TODO count stuffs
    int _cutCardPosition;
    int _hiloCount;
    

};

#endif