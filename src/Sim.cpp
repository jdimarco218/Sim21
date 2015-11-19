#include <iostream>
#include "Card.h"

int main(int argc, char ** argv)
{
    std::cout << "Starting sim." << std::endl;
    Card c1 = Card(2, 3);

    std::cout << "c1 rank: " << c1.getRank() << "  c1 suit: " << c1.getSuit() << std::endl;

    return 0;
}

