#include <iostream>
#include "Sim.h"
#include "Card.h"
//#include "Deck.h"
#include "Shoe.h"

int main(int argc, char ** argv)
{
    std::cout << "Starting sim." << std::endl;

    Sim sim = Sim(TSimMode::STRATEGY, TDeckType::SPANISH21);
    sim.RunSimulation();

    std::cout << "Done." << std::endl;

    return 0;
}

