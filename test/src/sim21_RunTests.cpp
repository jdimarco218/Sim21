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
#include "PlayHand_test.h"
#include "PlayHand_Sp21_test.h"
#include "SetInitialBet_test.h"
#include "GetDecision_test.h"
#include "GetTrueCount_test.h"
#include "GetPlayStrategy_test.h"
#include "Blackjack_Sp21_test.h"

int main(int argc, char ** argv)
{
    bool testsPassed = true;
    std::cout << "Starting test." << std::endl;

    std::vector<std::string> players;
    players.push_back("Player_0");
    players.push_back("Player_1");
    std::unique_ptr<Sim> sim(new Sim(TSimMode::STRATEGY, TDeckType::BLACKJACK, 1000, players));

    testsPassed &= PlayHandTest(sim);
    testsPassed &= GetOptimalValueTest(sim);
    testsPassed &= InsuranceTest(sim);
    testsPassed &= SetInitialBetTest(sim);
    testsPassed &= GetTrueCountTest(sim);
    testsPassed &= GetDecisionTest(sim);

    sim.reset(new Sim(TSimMode::STRATEGY, TDeckType::SPANISH21, 1000, players));
    testsPassed &= BlackjackSp21Test(sim);
    testsPassed &= PlayHandSp21Test(sim);
    testsPassed &= GetPlayStrategySp21Test(sim);

    if (testsPassed)
    {
        std::cout << "SUCCESS!" << std::endl;
    }
    else
    {
        std::cout << "WTF THIS SHIT FAILED!" << std::endl;
    }

    std::cout << "Done test." << std::endl;
    return 0;
}

