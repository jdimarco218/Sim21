#include <iostream>
#include <list>
#include <memory>
#include <vector>
#include "Sim.h"
#include "Card.h"
#include "Deck.h"
#include "Shoe.h"

// Test headers
#include "GetOptimalValue_test.h"
#include "Insurance_test.h"

int main(int argc, char ** argv)
{
    bool testsPassed = true;
    std::cout << "Starting test." << std::endl;

    std::unique_ptr<Sim> sim(new Sim(TSimMode::STRATEGY, TDeckType::SPANISH21));

    testsPassed &= GetOptimalValueTest(sim);
    testsPassed &= InsuranceTest(sim);

    if (testsPassed)
    {
        std::cout << "SUCCESS!" << std::endl;
    }
    else
    {
        std::cout << "WTF THIS SHIT FAILED!" << std::endl;
    }

    return 0;
}

