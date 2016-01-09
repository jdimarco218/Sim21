#include <assert.h>
#include <iostream>
#include <list>
#include <memory>
#include <vector>
#include "Sim.h"
#include "Card.h"
#include "Deck.h"
#include "Shoe.h"

#include "GetTrueCount_test.h"
#include "TestUtil.h"

bool GetTrueCountTest(std::unique_ptr<Sim>& sim, bool verbose)
{
    bool testPassed = true;

    testPassed &= GetHiloTrueCountTest(sim, verbose);

    return testPassed;
}

bool GetHiloTrueCountTest(std::unique_ptr<Sim>& sim, bool verbose)
{
    bool testPassed = true;
    bool preTest = true;

    std::string ref = "";
    int refCount = 0;

    // TEST CASE
    // TC of 0, 2 decks
    //
    ResetTestEnv(sim);
    ref = "GetHiloTrueCountTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, 0);
    SetShoeToNumCards(sim, 104); // Two decks
    testPassed &= 0 == sim->GetGame()->GetHiloTrueCount();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // TC of 1, 2 decks
    //
    ResetTestEnv(sim);
    ref = "GetHiloTrueCountTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, 2);
    SetShoeToNumCards(sim, 104); // Two decks
    testPassed &= 1 == sim->GetGame()->GetHiloTrueCount();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // TC of 2, 2 decks
    //
    ResetTestEnv(sim);
    ref = "GetHiloTrueCountTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, 4);
    SetShoeToNumCards(sim, 104); // Two decks
    testPassed &= 2 == sim->GetGame()->GetHiloTrueCount();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // TC of 3, 2 decks
    //
    ResetTestEnv(sim);
    ref = "GetHiloTrueCountTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, 6);
    SetShoeToNumCards(sim, 104); // Two decks
    testPassed &= 3 == sim->GetGame()->GetHiloTrueCount();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // TC of 4, 2 decks
    //
    ResetTestEnv(sim);
    ref = "GetHiloTrueCountTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, 8);
    SetShoeToNumCards(sim, 104); // Two decks
    testPassed &= 4 == sim->GetGame()->GetHiloTrueCount();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // TC of 5, 2 decks
    //
    ResetTestEnv(sim);
    ref = "GetHiloTrueCountTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, 10);
    SetShoeToNumCards(sim, 104); // Two decks
    testPassed &= 5 == sim->GetGame()->GetHiloTrueCount();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // TC of -1, 2 decks
    //
    ResetTestEnv(sim);
    ref = "GetHiloTrueCountTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, -2);
    SetShoeToNumCards(sim, 104); // Two decks
    testPassed &= -1 == sim->GetGame()->GetHiloTrueCount();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // TC of -2, 2 decks
    //
    ResetTestEnv(sim);
    ref = "GetHiloTrueCountTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, -4);
    SetShoeToNumCards(sim, 104); // Two decks
    testPassed &= -2 == sim->GetGame()->GetHiloTrueCount();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // TC of -3, 2 decks
    //
    ResetTestEnv(sim);
    ref = "GetHiloTrueCountTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, -6);
    SetShoeToNumCards(sim, 104); // Two decks
    testPassed &= -3 == sim->GetGame()->GetHiloTrueCount();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // TC of -4, 2 decks
    //
    ResetTestEnv(sim);
    ref = "GetHiloTrueCountTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, -8);
    SetShoeToNumCards(sim, 104); // Two decks
    testPassed &= -4 == sim->GetGame()->GetHiloTrueCount();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // TC of -5, 2 decks
    //
    ResetTestEnv(sim);
    ref = "GetHiloTrueCountTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, -10);
    SetShoeToNumCards(sim, 104); // Two decks
    testPassed &= -5 == sim->GetGame()->GetHiloTrueCount();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // TC of 0, 6 decks
    //
    ResetTestEnv(sim);
    ref = "GetHiloTrueCountTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, 0);
    SetShoeToNumCards(sim, 312); // Two decks
    testPassed &= 0 == sim->GetGame()->GetHiloTrueCount();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // TC of 1, 6 decks
    //
    ResetTestEnv(sim);
    ref = "GetHiloTrueCountTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, 6);
    SetShoeToNumCards(sim, 312); // Two decks
    testPassed &= 1 == sim->GetGame()->GetHiloTrueCount();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // TC of 2, 6 decks
    //
    ResetTestEnv(sim);
    ref = "GetHiloTrueCountTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, 12);
    SetShoeToNumCards(sim, 312); // Two decks
    testPassed &= 2 == sim->GetGame()->GetHiloTrueCount();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // TC of 3, 6 decks
    //
    ResetTestEnv(sim);
    ref = "GetHiloTrueCountTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, 18);
    SetShoeToNumCards(sim, 312); // Two decks
    testPassed &= 3 == sim->GetGame()->GetHiloTrueCount();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // TC of 4, 6 decks
    //
    ResetTestEnv(sim);
    ref = "GetHiloTrueCountTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, 24);
    SetShoeToNumCards(sim, 312); // Two decks
    testPassed &= 4 == sim->GetGame()->GetHiloTrueCount();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // TC of 5, 6 decks
    //
    ResetTestEnv(sim);
    ref = "GetHiloTrueCountTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, 30);
    SetShoeToNumCards(sim, 312); // Two decks
    testPassed &= 5 == sim->GetGame()->GetHiloTrueCount();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // TC of -1, 6 decks
    //
    ResetTestEnv(sim);
    ref = "GetHiloTrueCountTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, -6);
    SetShoeToNumCards(sim, 312); // Two decks
    testPassed &= -1 == sim->GetGame()->GetHiloTrueCount();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // TC of -2, 6 decks
    //
    ResetTestEnv(sim);
    ref = "GetHiloTrueCountTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, -12);
    SetShoeToNumCards(sim, 312); // Two decks
    testPassed &= -2 == sim->GetGame()->GetHiloTrueCount();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // TC of -3, 6 decks
    //
    ResetTestEnv(sim);
    ref = "GetHiloTrueCountTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, -18);
    SetShoeToNumCards(sim, 312); // Two decks
    testPassed &= -3 == sim->GetGame()->GetHiloTrueCount();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // TC of -4, 6 decks
    //
    ResetTestEnv(sim);
    ref = "GetHiloTrueCountTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, -24);
    SetShoeToNumCards(sim, 312); // Two decks
    testPassed &= -4 == sim->GetGame()->GetHiloTrueCount();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // TC of -5, 6 decks
    //
    ResetTestEnv(sim);
    ref = "GetHiloTrueCountTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, -30);
    SetShoeToNumCards(sim, 312); // Two decks
    testPassed &= -5 == sim->GetGame()->GetHiloTrueCount();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}


    return testPassed;
}
