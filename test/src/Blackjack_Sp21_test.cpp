#include <assert.h>
#include <iostream>
#include <list>
#include <memory>
#include <vector>
#include "Sim.h"
#include "Card.h"
#include "Deck.h"
#include "Shoe.h"

#include "Blackjack_Sp21_test.h"
#include "TestUtil.h"

//******************************************************************************
//
// Tests:
//
// Players will be paid out for blackjack regardless of the dealer having
//   blackjack
// Players should go inactive after receiving their blackjack payout
// Players should not be affected by SetWantsInsurance()
//
//******************************************************************************


/**
 * This tests the SPANISH21 blackjack component of CheckInsuranceAndBlackjack()
 */
bool BlackjackSp21Test(std::unique_ptr<Sim>& sim, bool verbose)
{
    bool testPassed = true;
    bool preTest = true;
    std::string ref = "";
    int refCount = 0;

    std::vector<int> ranks;
    std::vector<int> dealerRanks;

    // Test no insurance
    //
    sim->GetPlayerAt(0)->SetWantsInsurance(false);
    sim->GetPlayerAt(1)->SetWantsInsurance(false);

    // TEST CASE
    // Dealer does NOT have blackjack
    // Players have blackjack
    // Players don't want insurance
    //
    ResetTestEnv(sim);
    ref = "BlackjackTestSp21 " + std::to_string(refCount++);
    preTest = testPassed;
    ranks.clear();
    ranks.push_back(1);
    ranks.push_back(11); // player blackjack
    dealerRanks.push_back(11);
    dealerRanks.push_back(12); // dealer 20
    MakeHandForPlayerIdxHandIdx(sim, ranks, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    if(verbose){std::cout << "test. IsAceUp(): " << sim->IsAceUp() << std::endl;}
    sim->CheckInsuranceAndBlackjack();
    if(verbose){std::cout << "test. chips p0: " << sim->GetPlayerAt(0)->GetChips() << std::endl;}
    if(verbose){std::cout << "test. chips p1: " << sim->GetPlayerAt(1)->GetChips() << std::endl;}
    testPassed &= 37.5 == sim->GetPlayerAt(0)->GetChips();
    testPassed &= 37.5 == sim->GetPlayerAt(1)->GetChips();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // Dealer has blackjack with Ace up
    // Players have blackjack
    // Players don't want insurance
    //
    ResetTestEnv(sim);
    ref = "BlackjackTestSp21 " + std::to_string(refCount++);
    preTest = testPassed;
    ranks.clear();
    ranks.push_back(1);
    ranks.push_back(11); // player blackjack
    dealerRanks.push_back(1);
    dealerRanks.push_back(13); // dealer blackjack
    MakeHandForPlayerIdxHandIdx(sim, ranks, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    if(verbose){std::cout << "test. IsAceUp(): " << sim->IsAceUp() << std::endl;}
    sim->CheckInsuranceAndBlackjack();
    if(verbose){std::cout << "test. chips p0: " << sim->GetPlayerAt(0)->GetChips() << std::endl;}
    if(verbose){std::cout << "test. chips p1: " << sim->GetPlayerAt(1)->GetChips() << std::endl;}
    testPassed &= 37.5 == sim->GetPlayerAt(0)->GetChips();
    testPassed &= 37.5 == sim->GetPlayerAt(1)->GetChips();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // Dealer has blackjack without Ace up
    // Players have blackjack
    // Players don't want insurance
    //
    ResetTestEnv(sim);
    ref = "BlackjackTestSp21 " + std::to_string(refCount++);
    preTest = testPassed;
    ranks.clear();
    ranks.push_back(1);
    ranks.push_back(11); // player blackjack
    dealerRanks.push_back(11);
    dealerRanks.push_back(1); // dealer blackjack
    MakeHandForPlayerIdxHandIdx(sim, ranks, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    if(verbose){std::cout << "test. IsAceUp(): " << sim->IsAceUp() << std::endl;}
    sim->CheckInsuranceAndBlackjack();
    if(verbose){std::cout << "test. chips p0: " << sim->GetPlayerAt(0)->GetChips() << std::endl;}
    if(verbose){std::cout << "test. chips p1: " << sim->GetPlayerAt(1)->GetChips() << std::endl;}
    testPassed &= 37.5 == sim->GetPlayerAt(0)->GetChips();
    testPassed &= 37.5 == sim->GetPlayerAt(1)->GetChips();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // Dealer does NOT have blackjack
    // Players have blackjack
    // Players DO want insurance, not relevant
    //
    ResetTestEnv(sim);
    sim->GetPlayerAt(0)->SetWantsInsurance(true);
    sim->GetPlayerAt(1)->SetWantsInsurance(true);
    ref = "BlackjackTestSp21 " + std::to_string(refCount++);
    preTest = testPassed;
    ranks.clear();
    ranks.push_back(1);
    ranks.push_back(11); // player blackjack
    dealerRanks.push_back(11);
    dealerRanks.push_back(12); // dealer 20
    MakeHandForPlayerIdxHandIdx(sim, ranks, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    if(verbose){std::cout << "test. IsAceUp(): " << sim->IsAceUp() << std::endl;}
    sim->CheckInsuranceAndBlackjack();
    if(verbose){std::cout << "test. chips p0: " << sim->GetPlayerAt(0)->GetChips() << std::endl;}
    if(verbose){std::cout << "test. chips p1: " << sim->GetPlayerAt(1)->GetChips() << std::endl;}
    testPassed &= 37.5 == sim->GetPlayerAt(0)->GetChips();
    testPassed &= 37.5 == sim->GetPlayerAt(1)->GetChips();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // Dealer has blackjack with Ace up
    // Players have blackjack
    // Players DO want insurance
    //
    ResetTestEnv(sim);
    sim->GetPlayerAt(0)->SetWantsInsurance(true);
    sim->GetPlayerAt(1)->SetWantsInsurance(true);
    ref = "BlackjackTestSp21 " + std::to_string(refCount++);
    preTest = testPassed;
    ranks.clear();
    ranks.push_back(1);
    ranks.push_back(11); // player blackjack
    dealerRanks.push_back(1);
    dealerRanks.push_back(13); // dealer blackjack
    MakeHandForPlayerIdxHandIdx(sim, ranks, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    if(verbose){std::cout << "test. IsAceUp(): " << sim->IsAceUp() << std::endl;}
    sim->CheckInsuranceAndBlackjack();
    if(verbose){std::cout << "test. chips p0: " << sim->GetPlayerAt(0)->GetChips() << std::endl;}
    if(verbose){std::cout << "test. chips p1: " << sim->GetPlayerAt(1)->GetChips() << std::endl;}
    testPassed &= 37.5 == sim->GetPlayerAt(0)->GetChips();
    testPassed &= 37.5 == sim->GetPlayerAt(1)->GetChips();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // Dealer has blackjack without Ace up
    // Players have blackjack
    // Players DO want insurance
    //
    ResetTestEnv(sim);
    sim->GetPlayerAt(0)->SetWantsInsurance(true);
    sim->GetPlayerAt(1)->SetWantsInsurance(true);
    ref = "BlackjackTestSp21 " + std::to_string(refCount++);
    preTest = testPassed;
    ranks.clear();
    ranks.push_back(1);
    ranks.push_back(11); // player blackjack
    dealerRanks.push_back(11);
    dealerRanks.push_back(1); // dealer blackjack
    MakeHandForPlayerIdxHandIdx(sim, ranks, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    if(verbose){std::cout << "test. IsAceUp(): " << sim->IsAceUp() << std::endl;}
    sim->CheckInsuranceAndBlackjack();
    if(verbose){std::cout << "test. chips p0: " << sim->GetPlayerAt(0)->GetChips() << std::endl;}
    if(verbose){std::cout << "test. chips p1: " << sim->GetPlayerAt(1)->GetChips() << std::endl;}
    testPassed &= 37.5 == sim->GetPlayerAt(0)->GetChips();
    testPassed &= 37.5 == sim->GetPlayerAt(1)->GetChips();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}


    return testPassed;
}
