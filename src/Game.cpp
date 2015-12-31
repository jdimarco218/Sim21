#include <iostream>
#include <list>
#include <memory>
#include <random>
#include "Game.h"

std::unique_ptr<Card> Game::DealCard()
{
    if(!_shoe->IsEmpty())
    {
        //std::unique_ptr<Card> temp = std::move(_shoe->_shoeCards.front());
        //_shoe->_shoeCards.pop_front();
        const auto it = _shoe->_shoeCards.begin();
        auto temp = std::move(*it);//_shoe->_shoeCards.
        _shoe->_shoeCards.erase(it);
        return temp;
    }
    std::cerr << "ERROR: Shoe is empty. Cannot DealCard()" << std::endl;
    return std::move(std::unique_ptr<Card>(new Card(0, 1)));
}

Game::Game(TDeckType deckType, int numDecks, double minimumBet, int cutPercentMin, int cutPercentMax)
{
    _shoe = std::move(std::unique_ptr<Shoe>(new Shoe(numDecks, deckType)));
    _shoe->ShuffleCards();
    _hiloCount = 0;
    _minimumBet = minimumBet;
    _numSplits = 4;
    _resplitAces = false;
    _playSplitAces = false;
    _bonusPayOnSplitAces = false;
    _das = true;
    _s17 = true;

    // Generate a random cut card in the penetration range
    //
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(cutPercentMin, cutPercentMax);
    _cutCardPosition = dis(gen) * _shoe->GetCards().size() / 100; 
}

void Game::ResetGame()
{
    //TODO

    return;
}
