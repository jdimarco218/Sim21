#include <iostream>
#include <list>
#include <memory>
#include "Sim.h"
#include "Card.h"
#include "Deck.h"
#include "Shoe.h"

int main(int argc, char ** argv)
{
    std::cout << "Starting sim." << std::endl;

    std::unique_ptr<Sim> sim(new Sim(TSimMode::STRATEGY, TDeckType::SPANISH21));
    sim->RunSimulation();

    std::cout << "Done." << std::endl;

    //delete sim;

    return 0;
}

