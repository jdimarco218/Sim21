#include <assert.h>
#include <iostream>
#include <list>
#include <memory>
#include <vector>
#include "Sim.h"
#include "Card.h"
#include "Deck.h"
#include "Shoe.h"

#include "Insurance_test.h"
#include "TestUtil.h"


/**
 * This tests the insurance component of Sim::CheckInsuranceAndBlackjack()
 */
bool InsuranceTest(std::unique_ptr<Sim>& sim, bool verbose)
{
    bool testPassed = true;

    // We need players that both do and don't want insurance when the dealer
    // does and doesn't have blackjack.
    //
    sim->GetPlayerAt(0)->SetWantsInsurance(true);
    sim->GetPlayerAt(1)->SetWantsInsurance(false);

    std::vector<int> ranks;
    std::vector<int> dealerRanks;

    // TEST CASE
    // Dealer has blackjack with Ace up
    // No players have blackjack
    // Player 0 wants insurance
    // Player 1 doesn't want insurance
    //
    ResetTestEnv(sim);
    ranks.clear();
    ranks.push_back(10);
    ranks.push_back(11); // player 20
    dealerRanks.push_back(1);
    dealerRanks.push_back(10); // dealer blackjack
    MakeHandForPlayerIdxHandIdx(sim, ranks, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    if(verbose){std::cout << "test. IsAceUp(): " << sim->IsAceUp() << std::endl;}
    sim->CheckInsuranceAndBlackjack();
    if(verbose){std::cout << "test. chips p0: " << sim->GetPlayerAt(0)->GetChips() << std::endl;}
    if(verbose){std::cout << "test. chips p1: " << sim->GetPlayerAt(1)->GetChips() << std::endl;}
    testPassed &= 0   == sim->GetPlayerAt(0)->GetChips();
    testPassed &= -25 == sim->GetPlayerAt(1)->GetChips();
    
    // TEST CASE
    // Dealer has blackjack with Ace up
    // Both players have blackjack
    // Player 0 wants insurance
    // Player 1 doesn't want insurance
    //
    ResetTestEnv(sim);
    ranks.clear();
    dealerRanks.clear();
    ranks.push_back(1);
    ranks.push_back(11); // player blackjack
    dealerRanks.push_back(1);
    dealerRanks.push_back(10); // dealer blackjack
    MakeHandForPlayerIdxHandIdx(sim, ranks, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    if(verbose){std::cout << "test. IsAceUp(): " << sim->IsAceUp() << std::endl;}
    sim->CheckInsuranceAndBlackjack();
    if(verbose){std::cout << "test. chips p0: " << sim->GetPlayerAt(0)->GetChips() << std::endl;}
    if(verbose){std::cout << "test. chips p1: " << sim->GetPlayerAt(1)->GetChips() << std::endl;}
    testPassed &= 25 == sim->GetPlayerAt(0)->GetChips();
    testPassed &= 0  == sim->GetPlayerAt(1)->GetChips();

    // TEST CASE
    // Dealer has blackjack without Ace up
    // No players have blackjack
    // Neither player can get insurance
    //
    ResetTestEnv(sim);
    ranks.clear();
    dealerRanks.clear();
    ranks.push_back(8);
    ranks.push_back(11); // player 19
    dealerRanks.push_back(10); // up card
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
    testPassed &= -25 == sim->GetPlayerAt(0)->GetChips();
    testPassed &= -25 == sim->GetPlayerAt(1)->GetChips();

    // TEST CASE
    // Dealer has blackjack without Ace up
    // Both players have blackjack
    // Neither player can get insurance
    //
    ResetTestEnv(sim);
    ranks.clear();
    dealerRanks.clear();
    ranks.push_back(12);
    ranks.push_back(1); // player blackjack
    dealerRanks.push_back(13); // up card
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
    testPassed &= 0 == sim->GetPlayerAt(0)->GetChips();
    testPassed &= 0 == sim->GetPlayerAt(1)->GetChips();

    // TEST CASE
    // Dealer does not have blackjack but does have Ace up
    // Both players have blackjack
    // Neither player can ask for insurance
    //
    ResetTestEnv(sim);
    ranks.clear();
    dealerRanks.clear();
    ranks.push_back(1);
    ranks.push_back(12); // player blackjack
    dealerRanks.push_back(1);
    dealerRanks.push_back(9); // dealer A9
    MakeHandForPlayerIdxHandIdx(sim, ranks, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    if(verbose){std::cout << "test. IsAceUp(): " << sim->IsAceUp() << std::endl;}
    sim->CheckInsuranceAndBlackjack();
    if(verbose){std::cout << "test. chips p0: " << sim->GetPlayerAt(0)->GetChips() << std::endl;}
    if(verbose){std::cout << "test. chips p1: " << sim->GetPlayerAt(1)->GetChips() << std::endl;}
    testPassed &= 25   == sim->GetPlayerAt(0)->GetChips();
    testPassed &= 37.5 == sim->GetPlayerAt(1)->GetChips();

    // TEST CASE
    // Dealer does not have blackjack but does have Ace up
    // Neither player has blackjack
    // Neither player can ask for insurance
    //
    ResetTestEnv(sim);
    ranks.clear();
    dealerRanks.clear();
    ranks.push_back(1);
    ranks.push_back(8); // player no blackjack
    dealerRanks.push_back(1);
    dealerRanks.push_back(7); // no blackjack but ace up
    MakeHandForPlayerIdxHandIdx(sim, ranks, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    if(verbose){std::cout << "test. IsAceUp(): " << sim->IsAceUp() << std::endl;}
    sim->CheckInsuranceAndBlackjack();
    if(verbose){std::cout << "test. chips p0: " << sim->GetPlayerAt(0)->GetChips() << std::endl;}
    if(verbose){std::cout << "test. chips p1: " << sim->GetPlayerAt(1)->GetChips() << std::endl;}
    testPassed &= -37.5 == sim->GetPlayerAt(0)->GetChips();
    testPassed &= -25   == sim->GetPlayerAt(1)->GetChips();

    // TEST CASE
    // Dealer does not have blackjack nor Ace up
    // Both players have blackjack
    // Neither player can ask for insurance
    //
    ResetTestEnv(sim);
    ranks.clear();
    dealerRanks.clear();
    ranks.push_back(1);
    ranks.push_back(11); // player blackjack
    dealerRanks.push_back(6);
    dealerRanks.push_back(8); // not blackjack nor ace up
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
    testPassed &= 37.5  == sim->GetPlayerAt(1)->GetChips();

    // TEST CASE
    // Dealer does not have blackjack nor Ace up
    // Neither player has blackjack
    // Neither player can ask for insurance
    //
    ResetTestEnv(sim);
    ranks.clear();
    dealerRanks.clear();
    ranks.push_back(5);
    ranks.push_back(5); // not blackjack nor ace up
    dealerRanks.push_back(5);
    dealerRanks.push_back(5); // not blackjack nor ace up
    MakeHandForPlayerIdxHandIdx(sim, ranks, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    if(verbose){std::cout << "test. IsAceUp(): " << sim->IsAceUp() << std::endl;}
    sim->CheckInsuranceAndBlackjack();
    if(verbose){std::cout << "test. chips p0: " << sim->GetPlayerAt(0)->GetChips() << std::endl;}
    if(verbose){std::cout << "test. chips p1: " << sim->GetPlayerAt(1)->GetChips() << std::endl;}
    testPassed &= -25 == sim->GetPlayerAt(0)->GetChips();
    testPassed &= -25 == sim->GetPlayerAt(1)->GetChips();


    return testPassed;
}
