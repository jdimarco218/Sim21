#include <assert.h>
#include <iostream>
#include <list>
#include <memory>
#include <vector>
#include "Sim.h"
#include "Card.h"
#include "Deck.h"
#include "Shoe.h"

#include "SetInitialBet_test.h"
#include "TestUtil.h"

//******************************************************************************
//
// Tests:
//
// The SetInitialBet() method uses the Player's Strategy to determine the bet
// size. A child test should be created for each counting system to ensure
// the appropriate Bet is made for different conditions.
//
//
//******************************************************************************

/**
 * This test acts as a wrapper for the child tests. As a whole, it aims to test
 * the Player::SetInitialBet() method for different counts/Strategy's
 */
bool SetInitialBetTest(std::unique_ptr<Sim>& sim, bool verbose)
{
    bool testPassed = true;

    testPassed &= SetInitialBetHiloTest(sim, verbose);

    return testPassed;
}

//******************************************************************************
//
// TODO
//
//
// TODO
//
//******************************************************************************

/**
 * This tests the Hilo bet size of Player::SetInitialBet()
 */
bool SetInitialBetHiloTest(std::unique_ptr<Sim>& sim, bool verbose)
{
    bool testPassed = true;
    bool preTest = true;

    std::string ref = "";
    int refCount = 0;
    // Ensure players are counting
    // 
    sim->GetPlayerAt(0)->SetCounting(true);
    sim->GetPlayerAt(1)->SetCounting(true);

    ////
    // 2 deck tests
    ////

    // TEST CASE
    // Neutral count, players bet minimum
    //
    ResetTestEnv(sim);
    ref = "SetInitialBetHiloTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, 0);
    SetShoeToNumCards(sim, 104); // Two decks
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    testPassed &= 1 * sim->GetGame()->GetMinimumBet() == sim->GetPlayerAt(0)->GetHandBetAmount(0);
    testPassed &= 1 * sim->GetGame()->GetMinimumBet() == sim->GetPlayerAt(1)->GetHandBetAmount(0);
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // +1 TC, players bet minimum
    //
    ResetTestEnv(sim);
    ref = "SetInitialBetHiloTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, 2);
    SetShoeToNumCards(sim, 104); // Two decks
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    testPassed &= 1 * sim->GetGame()->GetMinimumBet() == sim->GetPlayerAt(0)->GetHandBetAmount(0);
    testPassed &= 1 * sim->GetGame()->GetMinimumBet() == sim->GetPlayerAt(1)->GetHandBetAmount(0);
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // +2 TC, players bet 2xUnits
    //
    ResetTestEnv(sim);
    ref = "SetInitialBetHiloTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, 4);
    SetShoeToNumCards(sim, 104); // Two decks
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    testPassed &= 2 * sim->GetGame()->GetMinimumBet() == sim->GetPlayerAt(0)->GetHandBetAmount(0);
    testPassed &= 2 * sim->GetGame()->GetMinimumBet() == sim->GetPlayerAt(1)->GetHandBetAmount(0);
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // +3 TC, players bet 4xUnits
    //
    ResetTestEnv(sim);
    ref = "SetInitialBetHiloTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, 6);
    SetShoeToNumCards(sim, 104); // Two decks
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    testPassed &= 4 * sim->GetGame()->GetMinimumBet() == sim->GetPlayerAt(0)->GetHandBetAmount(0);
    testPassed &= 4 * sim->GetGame()->GetMinimumBet() == sim->GetPlayerAt(1)->GetHandBetAmount(0);
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // +4 TC, players bet 8xUnits
    //
    ResetTestEnv(sim);
    ref = "SetInitialBetHiloTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, 8);
    SetShoeToNumCards(sim, 104); // Two decks
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    testPassed &= 8 * sim->GetGame()->GetMinimumBet() == sim->GetPlayerAt(0)->GetHandBetAmount(0);
    testPassed &= 8 * sim->GetGame()->GetMinimumBet() == sim->GetPlayerAt(1)->GetHandBetAmount(0);
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // +5 TC, players bet 12xUnits
    //
    ResetTestEnv(sim);
    ref = "SetInitialBetHiloTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, 10);
    SetShoeToNumCards(sim, 104); // Two decks
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    testPassed &= 12 * sim->GetGame()->GetMinimumBet() == sim->GetPlayerAt(0)->GetHandBetAmount(0);
    testPassed &= 12 * sim->GetGame()->GetMinimumBet() == sim->GetPlayerAt(1)->GetHandBetAmount(0);
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // +35 TC, players bet 12xUnits
    //
    ResetTestEnv(sim);
    ref = "SetInitialBetHiloTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, 70);
    SetShoeToNumCards(sim, 104); // Two decks
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    testPassed &= 12 * sim->GetGame()->GetMinimumBet() == sim->GetPlayerAt(0)->GetHandBetAmount(0);
    testPassed &= 12 * sim->GetGame()->GetMinimumBet() == sim->GetPlayerAt(1)->GetHandBetAmount(0);
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // -1 TC, players bet minimum
    //
    ResetTestEnv(sim);
    ref = "SetInitialBetHiloTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, -2);
    SetShoeToNumCards(sim, 104); // Two decks
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    testPassed &= 1 * sim->GetGame()->GetMinimumBet() == sim->GetPlayerAt(0)->GetHandBetAmount(0);
    testPassed &= 1 * sim->GetGame()->GetMinimumBet() == sim->GetPlayerAt(1)->GetHandBetAmount(0);
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // -17 TC, players bet minimum
    //
    ResetTestEnv(sim);
    ref = "SetInitialBetHiloTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, -34);
    SetShoeToNumCards(sim, 104); // Two decks
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    testPassed &= 1 * sim->GetGame()->GetMinimumBet() == sim->GetPlayerAt(0)->GetHandBetAmount(0);
    testPassed &= 1 * sim->GetGame()->GetMinimumBet() == sim->GetPlayerAt(1)->GetHandBetAmount(0);
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    ////
    // 3-5 deck tests
    ////

    // TEST CASE
    // Neutral count, players bet minimum
    //
    ResetTestEnv(sim);
    ref = "SetInitialBetHiloTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, 0);
    SetShoeToNumCards(sim, 182); // 3.5 decks
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    testPassed &= 1 * sim->GetGame()->GetMinimumBet() == sim->GetPlayerAt(0)->GetHandBetAmount(0);
    testPassed &= 1 * sim->GetGame()->GetMinimumBet() == sim->GetPlayerAt(1)->GetHandBetAmount(0);
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // +1 TC, players bet minimum
    //
    ResetTestEnv(sim);
    ref = "SetInitialBetHiloTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, 4);
    SetShoeToNumCards(sim, 182); // 3.5 decks
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    testPassed &= 1 * sim->GetGame()->GetMinimumBet() == sim->GetPlayerAt(0)->GetHandBetAmount(0);
    testPassed &= 1 * sim->GetGame()->GetMinimumBet() == sim->GetPlayerAt(1)->GetHandBetAmount(0);
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // +2 TC, players bet 2xUnits
    //
    ResetTestEnv(sim);
    ref = "SetInitialBetHiloTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, 7);
    SetShoeToNumCards(sim, 182); // 3.5 decks
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    testPassed &= 2 * sim->GetGame()->GetMinimumBet() == sim->GetPlayerAt(0)->GetHandBetAmount(0);
    testPassed &= 2 * sim->GetGame()->GetMinimumBet() == sim->GetPlayerAt(1)->GetHandBetAmount(0);
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // +3 TC, players bet 4xUnits
    //
    ResetTestEnv(sim);
    ref = "SetInitialBetHiloTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, 11);
    SetShoeToNumCards(sim, 182); // 3.5 decks
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    testPassed &= 4 * sim->GetGame()->GetMinimumBet() == sim->GetPlayerAt(0)->GetHandBetAmount(0);
    testPassed &= 4 * sim->GetGame()->GetMinimumBet() == sim->GetPlayerAt(1)->GetHandBetAmount(0);
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // +4 TC, players bet 8xUnits
    //
    ResetTestEnv(sim);
    ref = "SetInitialBetHiloTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, 14);
    SetShoeToNumCards(sim, 182); // 3.5 decks
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    testPassed &= 8 * sim->GetGame()->GetMinimumBet() == sim->GetPlayerAt(0)->GetHandBetAmount(0);
    testPassed &= 8 * sim->GetGame()->GetMinimumBet() == sim->GetPlayerAt(1)->GetHandBetAmount(0);
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // +5 TC, players bet 12xUnits
    //
    ResetTestEnv(sim);
    ref = "SetInitialBetHiloTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, 18);
    SetShoeToNumCards(sim, 182); // 3.5 decks
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    testPassed &= 12 * sim->GetGame()->GetMinimumBet() == sim->GetPlayerAt(0)->GetHandBetAmount(0);
    testPassed &= 12 * sim->GetGame()->GetMinimumBet() == sim->GetPlayerAt(1)->GetHandBetAmount(0);
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // +35 TC, players bet 12xUnits
    //
    ResetTestEnv(sim);
    ref = "SetInitialBetHiloTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, 123);
    SetShoeToNumCards(sim, 182); // 3.5 decks
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    testPassed &= 12 * sim->GetGame()->GetMinimumBet() == sim->GetPlayerAt(0)->GetHandBetAmount(0);
    testPassed &= 12 * sim->GetGame()->GetMinimumBet() == sim->GetPlayerAt(1)->GetHandBetAmount(0);
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // -1 TC, players bet minimum
    //
    ResetTestEnv(sim);
    ref = "SetInitialBetHiloTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, -4);
    SetShoeToNumCards(sim, 182); // 3.5 decks
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    testPassed &= 1 * sim->GetGame()->GetMinimumBet() == sim->GetPlayerAt(0)->GetHandBetAmount(0);
    testPassed &= 1 * sim->GetGame()->GetMinimumBet() == sim->GetPlayerAt(1)->GetHandBetAmount(0);
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // -17 TC, players bet minimum
    //
    ResetTestEnv(sim);
    ref = "SetInitialBetHiloTest " + std::to_string(refCount++);
    preTest = testPassed;
    SetHiloCount(sim, -60);
    SetShoeToNumCards(sim, 182); // 3.5 decks
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    testPassed &= 1 * sim->GetGame()->GetMinimumBet() == sim->GetPlayerAt(0)->GetHandBetAmount(0);
    testPassed &= 1 * sim->GetGame()->GetMinimumBet() == sim->GetPlayerAt(1)->GetHandBetAmount(0);
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    return testPassed;
}
