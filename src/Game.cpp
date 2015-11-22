#include <random>
#include "Game.h"

Game::Game(TDeckType deckType, int numDecks, int cutPercentMin, int cutPercentMax)
{
    _shoe = Shoe(numDecks, deckType);

    // Generate a random cut card in the penetration range
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(cutPercentMin, cutPercentMax);
    _cutCardPosition = dis(gen) * _shoe.GetCards().size() / 100; 

}
