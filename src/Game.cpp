#include <iostream>
#include <list>
#include <memory>
#include <random>
#include "Game.h"

std::unique_ptr<Card> Game::DealCard()
{
    if(!_shoe->IsEmpty())
    {
        std::cout << "Grabbing the front..." << std::endl;
        std::unique_ptr<Card> temp = std::move(_shoe->_shoeCards.front());
        std::cout << "Popping the front..." << std::endl;
        _shoe->_shoeCards.pop_front();
        std::cout << "Returning..." << std::endl;
        //return std::move(temp);
        return temp;
    }
    std::cerr << "ERROR: Shoe is empty. Cannot DealCard()" << std::endl;
    return std::move(std::unique_ptr<Card>(new Card(0, 1)));
}

Game::Game(TDeckType deckType, int numDecks, int cutPercentMin, int cutPercentMax)
{
    _shoe = std::move(std::unique_ptr<Shoe>(new Shoe(numDecks, deckType)));
    _hiloCount = 0;

    // Generate a random cut card in the penetration range
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(cutPercentMin, cutPercentMax);
    _cutCardPosition = dis(gen) * _shoe->GetCards().size() / 100; 
}
