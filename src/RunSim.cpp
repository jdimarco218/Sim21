#include <chrono>
#include <iostream>
#include <list>
#include <memory>
#include "Sim.h"
#include "Card.h"
#include "Deck.h"
#include "Shoe.h"

using namespace std::chrono;

int main(int argc, char ** argv)
{
    std::cout << "Starting sim." << std::endl;

    auto start = std::chrono::steady_clock::now();

    std::unique_ptr<Sim> sim(new Sim(TSimMode::STRATEGY, TDeckType::BLACKJACK));
    sim->GetPlayerAt(1)->SetCounting(false);
    sim->GetPlayerAt(1)->SetDeviating(false);
    sim->RunSimulation();

    auto end = std::chrono::steady_clock::now();
    auto timeSpan = std::chrono::duration_cast<duration<double> >(end - start);

    std::cout << "Done. Elapsed time: "
              << timeSpan.count()
              << " seconds."
              << std::endl;

    //delete sim;

    return 0;
}

