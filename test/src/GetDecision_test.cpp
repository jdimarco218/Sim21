#include <assert.h>
#include <iostream>
#include <list>
#include <memory>
#include <vector>
#include "Sim.h"
#include "Card.h"
#include "Deck.h"
#include "Shoe.h"

#include "GetDecision_test.h"
#include "TestUtil.h"

bool GetDecisionTest(std::unique_ptr<Sim>& sim, bool verbose)
{
    bool testPassed = true;

    testPassed &= GetDecisionDeviatingTest(sim, verbose);

    return testPassed;
}

bool GetDecisionDeviatingTest(std::unique_ptr<Sim>& sim, bool verbose)
{
    bool testPassed = true;
    bool preTest = true;

    std::string ref = "";
    int refCount = 0;

    std::vector<int> ranks0;
    std::vector<int> ranks1;
    std::vector<int> dealerRanks;

    // TEST CASE
    // Players' 9 v 2
    // TC +2
    // Player 0 deviates and doubles
    // Player 1 hits
    //
    ResetTestEnv(sim);
    ref = "GetDecisionDeviationTest " + std::to_string(refCount++);
    preTest = testPassed;
    sim->GetPlayerAt(0)->SetCounting(true);
    sim->GetPlayerAt(0)->SetDeviating(true);
    sim->GetPlayerAt(1)->SetCounting(false);
    sim->GetPlayerAt(1)->SetDeviating(false);
    ranks0.clear();
    ranks1.clear();
    dealerRanks.clear();
    ranks0.push_back(3);
    ranks0.push_back(6);
    ranks1.push_back(3);
    ranks1.push_back(6);
    dealerRanks.push_back(2);
    dealerRanks.push_back(10); // dealer 2 up
    MakeHandForPlayerIdxHandIdx(sim, ranks0, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks1, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    SetHiloCount(sim, 4);
    SetShoeToNumCards(sim, 104); // Two decks, TC +2
    testPassed &= TPlayAction::DOUBLE == sim->GetDecision(sim->GetPlayerAt(0),
                                                          sim->GetPlayerAt(0)->GetHand(0), 
                                                          false);
    testPassed &= TPlayAction::HIT    == sim->GetDecision(sim->GetPlayerAt(1),
                                                          sim->GetPlayerAt(1)->GetHand(0), 
                                                          false);
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // Players' 16 v 10
    // TC +1
    // Player 0 deviates, but surrenders as allowed
    // Player 1 surrenders
    //
    ResetTestEnv(sim);
    ref = "GetDecisionDeviationTest " + std::to_string(refCount++);
    preTest = testPassed;
    sim->GetGame()->SetLateSurrender(true);
    sim->GetPlayerAt(0)->SetCounting(true);
    sim->GetPlayerAt(0)->SetDeviating(true);
    sim->GetPlayerAt(1)->SetCounting(false);
    sim->GetPlayerAt(1)->SetDeviating(false);
    ranks0.clear();
    ranks1.clear();
    dealerRanks.clear();
    ranks0.push_back(11);
    ranks0.push_back(6);
    ranks1.push_back(11);
    ranks1.push_back(6);
    dealerRanks.push_back(10);
    dealerRanks.push_back(10); // dealer T up
    MakeHandForPlayerIdxHandIdx(sim, ranks0, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks1, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    SetHiloCount(sim, 2);
    SetShoeToNumCards(sim, 104); // Two decks, TC +1
    testPassed &= TPlayAction::SURRENDER == sim->GetDecision(sim->GetPlayerAt(0),
                                                          sim->GetPlayerAt(0)->GetHand(0), 
                                                          false);
    testPassed &= TPlayAction::SURRENDER == sim->GetDecision(sim->GetPlayerAt(1),
                                                          sim->GetPlayerAt(1)->GetHand(0), 
                                                          false);
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // Players' 16 v 10
    // TC +1
    // Player 0 deviates, and stands due to no late surrender
    // Player 1 hits
    //
    ResetTestEnv(sim);
    ref = "GetDecisionDeviationTest " + std::to_string(refCount++);
    preTest = testPassed;
    sim->GetGame()->SetLateSurrender(false);
    sim->GetPlayerAt(0)->SetCounting(true);
    sim->GetPlayerAt(0)->SetDeviating(true);
    sim->GetPlayerAt(1)->SetCounting(false);
    sim->GetPlayerAt(1)->SetDeviating(false);
    ranks0.clear();
    ranks1.clear();
    dealerRanks.clear();
    ranks0.push_back(11);
    ranks0.push_back(6);
    ranks1.push_back(11);
    ranks1.push_back(6);
    dealerRanks.push_back(10);
    dealerRanks.push_back(10); // dealer T up
    MakeHandForPlayerIdxHandIdx(sim, ranks0, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks1, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    SetHiloCount(sim, 2);
    SetShoeToNumCards(sim, 104); // Two decks, TC +1
    testPassed &= TPlayAction::STAND == sim->GetDecision(sim->GetPlayerAt(0),
                                                         sim->GetPlayerAt(0)->GetHand(0), 
                                                         false);
    testPassed &= TPlayAction::HIT   == sim->GetDecision(sim->GetPlayerAt(1),
                                                         sim->GetPlayerAt(1)->GetHand(0), 
                                                         false);
    sim->GetGame()->SetLateSurrender(true);
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}


    return testPassed;
}
