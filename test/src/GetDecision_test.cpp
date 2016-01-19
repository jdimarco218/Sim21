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

    // Capture rules before this set of tests
    //
    int  prevNumSplits = sim->GetGame()->GetNumSplits();

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
                                                          sim->GetPlayerAt(0)->GetHand(0));
    testPassed &= TPlayAction::HIT    == sim->GetDecision(sim->GetPlayerAt(1),
                                                          sim->GetPlayerAt(1)->GetHand(0));
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
                                                          sim->GetPlayerAt(0)->GetHand(0));
    testPassed &= TPlayAction::SURRENDER == sim->GetDecision(sim->GetPlayerAt(1),
                                                          sim->GetPlayerAt(1)->GetHand(0));
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
                                                         sim->GetPlayerAt(0)->GetHand(0));
    testPassed &= TPlayAction::HIT   == sim->GetDecision(sim->GetPlayerAt(1),
                                                         sim->GetPlayerAt(1)->GetHand(0));
    sim->GetGame()->SetLateSurrender(true);
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // Players' p8 v 10, no LS, no split
    // TC +1
    // Player 0 deviates, and stands due to no late surrender
    // Player 1 cannot surrender, and cannot split
    //
    ResetTestEnv(sim);
    ref = "GetDecisionDeviationTest " + std::to_string(refCount++);
    preTest = testPassed;
    sim->GetGame()->SetLateSurrender(false);
    sim->GetGame()->SetNumSplits(1); // no splits!
    sim->GetPlayerAt(0)->SetCounting(true);
    sim->GetPlayerAt(0)->SetDeviating(true);
    sim->GetPlayerAt(1)->SetCounting(false);
    sim->GetPlayerAt(1)->SetDeviating(false);
    ranks0.clear();
    ranks1.clear();
    dealerRanks.clear();
    ranks0.push_back(8);
    ranks0.push_back(8);
    ranks1.push_back(8);
    ranks1.push_back(8);
    dealerRanks.push_back(10);
    dealerRanks.push_back(10); // dealer T up
    MakeHandForPlayerIdxHandIdx(sim, ranks0, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks1, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    SetHiloCount(sim, 2);
    SetShoeToNumCards(sim, 104); // Two decks, TC +1
    testPassed &= TPlayAction::STAND == sim->GetDecision(sim->GetPlayerAt(0),
                                                         sim->GetPlayerAt(0)->GetHand(0));
    testPassed &= TPlayAction::HIT   == sim->GetDecision(sim->GetPlayerAt(1),
                                                         sim->GetPlayerAt(1)->GetHand(0));
    sim->GetGame()->SetLateSurrender(true);
    sim->GetGame()->SetNumSplits(prevNumSplits); // reset splits
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // J5e3
    // Players' 13v2
    // TC -3
    // Player 0 deviates and hits
    // Player 1 stands
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
    ranks0.push_back(8);
    ranks0.push_back(5);
    ranks1.push_back(8);
    ranks1.push_back(5);
    dealerRanks.push_back(2);
    dealerRanks.push_back(2); // dealer 2 up
    MakeHandForPlayerIdxHandIdx(sim, ranks0, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks1, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    SetHiloCount(sim, -6);
    SetShoeToNumCards(sim, 104); // Two decks, TC +1
    testPassed &= TPlayAction::HIT   == sim->GetDecision(sim->GetPlayerAt(0),
                                                         sim->GetPlayerAt(0)->GetHand(0));
    testPassed &= TPlayAction::STAND == sim->GetDecision(sim->GetPlayerAt(1),
                                                         sim->GetPlayerAt(1)->GetHand(0));
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}


    return testPassed;
}
