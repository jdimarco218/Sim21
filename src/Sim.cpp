#include <iostream>
#include "Card.h"
#include "Deck.h"
#include "Shoe.h"

int main(int argc, char ** argv)
{
    std::cout << "Starting sim." << std::endl;
    Card c1 = Card(2, 3);

    std::cout << "c1 rank: " << c1.GetRank() << "  c1 suit: " << c1.GetSuit() << std::endl;

    Shoe s1 = Shoe(2, TDeckType::SPANISH21);

    for(auto card : s1.GetCards())
    {
        std::cout << "card rank: " << card.GetRank() << "  card suit: " << card.GetSuit() << std::endl;
    }

    return 0;
}

