#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "Card.h"
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
    void ResetGame();
    void SetNumDoubles(int numDoubles){ _numDoubles = numDoubles; }
    void SetNumSplits(int numSplits){ _numSplits = numSplits; }
    void SetResplitAces(bool resplitAces){ _resplitAces = resplitAces; }
    void SetPlaySplitAces(bool playSplitAces){ _playSplitAces = playSplitAces; }
    void SetBonusPayOnSplitAces(bool bonus){ _bonusPayOnSplitAces = bonus; }
    void SetH17(bool h17){ _s17 = !h17; }
    void SetS17(bool s17){ _s17 = s17; }
    void SetLateSurrender(bool ls){ _lateSurrender = ls; }
    void SetNumSplitAces(bool nsa){ _numSplitAces = nsa; }
    double GetHiloTrueCount();
    int GetNumCardsDealt();
    inline TDeckType GetDeckType(){ return _deckType; }
    inline int  GetHiloCount(){ return _hiloCount; }
    inline int GetCutCardPosition(){ return _cutCardPosition; }
    inline int GetCardsRemaining(){ return _shoe->GetCardsRemaining(); }
    std::unique_ptr<Card> DealCard();
    inline double GetMinimumBet(){ return _minimumBet; }
    inline int GetNumDoubles(){ return _numDoubles; }
    inline int GetNumSplits(){ return _numSplits; }
    inline bool GetResplitAces(){ return _resplitAces; }
    inline bool GetNumSplitAces() { return _numSplitAces; }
    inline bool GetPlaySplitAces(){ return _playSplitAces; }
    inline bool GetBonusPayOnSplitAces(){ return _bonusPayOnSplitAces; }
    inline bool GetDaS(){ return _das; }
    inline bool GetS17(){ return _s17; }
    inline bool IsS17(){ return _s17; }
    inline bool GetH17(){ return !_s17; }
    inline bool IsH17(){ return !_s17; }
    inline bool IsLateSurrender(){ return _lateSurrender; }
    inline std::unique_ptr<Shoe>& GetShoe(){ return _shoe; }

    Game()
    {
        _shoe = std::move(std::unique_ptr<Shoe>(new Shoe()));
        _cutCardPosition = 0;
        _hiloCount = 0;
        _minimumBet = 25;
    }

    Game(TDeckType deckType,
         int numDecks = 6,
         double minimumBet = 25,
         int cutPercentMin = 75,
         int cutPercentMax = 80);

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
    int _numDoubles;
    int _numSplits;
    int _numSplitAces;
    bool _resplitAces;
    bool _playSplitAces;
    bool _bonusPayOnSplitAces;
    bool _das;
    bool _s17;
    bool _lateSurrender;
    TDeckType _deckType;

};

#endif
