#include <iostream>
#include <list>
#include <memory>
#include <random>
#include "Game.h"

std::unique_ptr<Card> Game::DealCard()
{
    if(!_shoe->IsEmpty())
    {
        const auto it = _shoe->_shoeCards.begin();
        if ((*it)->GetRank() == 0)
        {
            std::cerr << "WTF ZERO" << std::endl;
        }
        if ((*it)->GetRank() == 1)
        {
            _hiloCount -= 1;
        }
        else if ((*it)->GetRank() < 7)
        {
            _hiloCount += 1;
        }
        else if ((*it)->GetRank() >= 10)
        {
            _hiloCount -= 1;
        }
        auto temp = std::move(*it);
        _shoe->_shoeCards.erase(it);
        return temp;
    }
    std::cerr << "ERROR: Shoe is empty. Cannot DealCard()" << std::endl;
    return std::move(std::unique_ptr<Card>(new Card(0, 1)));
}

Game::Game(TDeckType deckType, int numDecks, double minimumBet, int cutPercentMin, int cutPercentMax)
{
    _deckType = deckType;
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
    _numSplitAces = 3;

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

double Game::GetHiloTrueCount()
{
    return static_cast<double>(_hiloCount) / _shoe->GetNumDecksRemaining();
}

int Game::GetNumCardsDealt()
{
    return _shoe->GetNumStartingCards() - _shoe->GetCardsRemaining();
}
