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
    void ResetGame(){}
    inline int GetCutCardPosition(){ return _cutCardPosition; }
    inline int GetCardsRemaining(){ return _shoe->GetCardsRemaining(); }
    std::unique_ptr<Card> DealCard();
    double GetMinimumBet(){ return _minimumBet; }
    inline int GetNumSplits(){ return _numSplits; }
    inline std::unique_ptr<Shoe>& GetShoe(){ return _shoe; }

    Game()
    {
        _shoe = std::move(std::unique_ptr<Shoe>(new Shoe()));
        _cutCardPosition = 0;
        _hiloCount = 0;
        _minimumBet = 25;
    }
    Game(TDeckType deckType, int numDecks = 6, double minimumBet = 25, int cutPercentMin = 75, int cutPercentMax = 80);
    ~Game()
    {
        //std::cout << "Game dtor." << std::endl;
    }  

private:
    std::unique_ptr<Shoe> _shoe;
    // TODO count stuffs
    int _cutCardPosition;
    int _hiloCount;
    double _minimumBet;
    int _numSplits;
    

};

#endif
