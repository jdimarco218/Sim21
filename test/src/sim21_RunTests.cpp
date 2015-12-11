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

/**
 * Helper function to create a hand
 */
//void MakeHand(std::vector<std::unique_ptr<Card> >& hand, std::vector<int> ranks)
//{
//    // Start with an empty hand
//    hand.clear();
//
//    // Populate the hand with the input ranks
//    for (auto i : ranks)
//    {
//        // All suited as "1", who cares?
//        hand.push_back(std::unique_ptr<Card>(new Card(i, 1)));
//    }
//
//    return;
//}
//
///**
// * This tests Sim::GetOptimalValue()
// */
//bool GetOptimalValueTest(std::unique_ptr<Sim>& sim)
//{
//    bool testPassed = true;
//
//    // Make different hands and check the result
//    std::vector<std::unique_ptr<Card> > hand;
//    std::vector<int> ranks;
//
//    // TEST CASE
//    hand.clear();
//    ranks.clear();
//    ranks.push_back(1);
//    ranks.push_back(10);
//    MakeHand(hand, ranks);
//
//    testPassed &= 21 == sim->GetOptimalValue(hand);
//    if (!testPassed)
//    {
//        std::cout << "Test 1 failed with value: " 
//                  << sim->GetOptimalValue(hand)
//                  << std::endl;
//    }
//
//    // TEST CASE
//    hand.clear();
//    ranks.clear();
//    ranks.push_back(1);
//    ranks.push_back(9);
//    MakeHand(hand, ranks);
//
//    testPassed &= 20 == sim->GetOptimalValue(hand);
//    if (!testPassed)
//    {
//        std::cout << "Test 2 failed with value: " 
//                  << sim->GetOptimalValue(hand)
//                  << std::endl;
//    }
//
//    // TEST CASE
//    hand.clear();
//    ranks.clear();
//    ranks.push_back(1);
//    ranks.push_back(1);
//    ranks.push_back(1);
//    ranks.push_back(1);
//    ranks.push_back(1);
//    ranks.push_back(1);
//    ranks.push_back(1);
//    MakeHand(hand, ranks);
//
//    testPassed &= 17 == sim->GetOptimalValue(hand);
//    if (!testPassed)
//    {
//        std::cout << "Test 3 failed with value: " 
//                  << sim->GetOptimalValue(hand)
//                  << std::endl;
//    }
//
//    // TEST CASE
//    hand.clear();
//    ranks.clear();
//    ranks.push_back(7);
//    ranks.push_back(8);
//    MakeHand(hand, ranks);
//
//    testPassed &= 15 == sim->GetOptimalValue(hand);
//    if (!testPassed)
//    {
//        std::cout << "Test 4 failed with value: " 
//                  << sim->GetOptimalValue(hand)
//                  << std::endl;
//    }
//
//    // TEST CASE
//    hand.clear();
//    ranks.clear();
//    ranks.push_back(1);
//    ranks.push_back(1);
//    ranks.push_back(8);
//    MakeHand(hand, ranks);
//
//    testPassed &= 20 == sim->GetOptimalValue(hand);
//    if (!testPassed)
//    {
//        std::cout << "Test 5 failed with value: " 
//                  << sim->GetOptimalValue(hand)
//                  << std::endl;
//    }
//
//    // TEST CASE
//    hand.clear();
//    ranks.clear();
//    ranks.push_back(7);
//    ranks.push_back(7);
//    ranks.push_back(7);
//    MakeHand(hand, ranks);
//
//    testPassed &= 21 == sim->GetOptimalValue(hand);
//    if (!testPassed)
//    {
//        std::cout << "Test 6 failed with value: " 
//                  << sim->GetOptimalValue(hand)
//                  << std::endl;
//    }
//
//    // TEST CASE
//    hand.clear();
//    ranks.clear();
//    ranks.push_back(1);
//    ranks.push_back(1);
//    MakeHand(hand, ranks);
//
//    testPassed &= 12 == sim->GetOptimalValue(hand);
//    if (!testPassed)
//    {
//        std::cout << "Test 7 failed with value: " 
//                  << sim->GetOptimalValue(hand)
//                  << std::endl;
//    }
//
//    // TEST CASE
//    hand.clear();
//    ranks.clear();
//    ranks.push_back(2);
//    ranks.push_back(2);
//    MakeHand(hand, ranks);
//
//    testPassed &= 4 == sim->GetOptimalValue(hand);
//    if (!testPassed)
//    {
//        std::cout << "Test 8 failed with value: " 
//                  << sim->GetOptimalValue(hand)
//                  << std::endl;
//    }
//
//    return testPassed;
//}

int main(int argc, char ** argv)
{
    bool testsPassed = true;
    std::cout << "Starting test." << std::endl;

    std::unique_ptr<Sim> sim(new Sim(TSimMode::STRATEGY, TDeckType::SPANISH21));

    testsPassed &= GetOptimalValueTest(sim);

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

