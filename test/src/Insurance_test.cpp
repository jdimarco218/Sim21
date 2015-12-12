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

/**
 * Helper function to create a player's specific hand
 */
void MakeHandForPlayerIdxHandIdx(std::unique_ptr<Sim>& sim, std::vector<int> ranks, int pIdx, int hIdx)
{

    // Assert this is a new or existing hand
    assert(sim->GetPlayerAt(pIdx)->GetHands().size() >= hIdx && "Must be a new or existing hand index!");

    // Insert the hand at the correct index
    if(sim->GetPlayerAt(pIdx)->GetHands().size() == hIdx)
    {
        // New hand, populate a new one
        std::vector<std::unique_ptr<Card> > hand;
        hand.clear();

        for (auto i : ranks)
        {
            // All suited as "1", who cares?
            hand.push_back(std::unique_ptr<Card>(new Card(i, 1)));
        }

        sim->GetPlayerAt(pIdx)->GetHands().push_back(std::move(hand));
    }
    else
    {
        // Existing hand, update it
        std::vector<std::unique_ptr<Card> >& hand = sim->GetPlayerAt(pIdx)->GetHand(hIdx);
        hand.clear();

        for (auto i : ranks)
        {
            // All suited as "1", who cares?
            hand.push_back(std::unique_ptr<Card>(new Card(i, 1)));
        }
    }

    return;
}

void MakeHandForDealer(std::unique_ptr<Sim>& sim, std::vector<int> ranks)
{
    // If dealer has a hand already, clear it
    assert(sim->GetDealer()->GetHands().size() == 1 && "Dealer must have one hand during InsuranceTest()");
    //if(sim->GetDealer()->GetHand(0).size() > 0)
    //{
    //    sim->GetDealer()->GetHand(0).clear();
    //}

    // Insert the hand at the zero'th index
    std::vector<std::unique_ptr<Card> >& hand = sim->GetDealer()->GetHand(0);
    hand.clear();

    for (auto i : ranks)
    {
        // All suited as "1", who cares?
        hand.push_back(std::unique_ptr<Card>(new Card(i, 1)));
    }

    return;
}

/**
 * This tests the insurance component of Sim::CheckInsuranceAndBlackjack()
 */
bool InsuranceTest(std::unique_ptr<Sim>& sim)
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
    // Dealer has blackjack
    // No players have blackjack
    // Player 0 wants insurance
    // Player 1 doesn't want insurance
    //
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
    std::cout << "test. IsAceUp(): " << sim->IsAceUp() << std::endl;
    sim->CheckInsuranceAndBlackjack();
    std::cout << "test. chips p0: " << sim->GetPlayerAt(0)->GetChips() << std::endl;
    std::cout << "test. chips p1: " << sim->GetPlayerAt(1)->GetChips() << std::endl;
    testPassed &= 0   == sim->GetPlayerAt(0)->GetChips();
    testPassed &= -25 == sim->GetPlayerAt(1)->GetChips();
    
    // TEST CASE
    // Dealer has blackjack
    // Both players have blackjack
    // Player 0 wants insurance
    // Player 1 doesn't want insurance
    //
    ranks.clear();
    ranks.push_back(1);
    ranks.push_back(11); // player blackjack
    dealerRanks.push_back(1);
    dealerRanks.push_back(10); // dealer blackjack
    MakeHandForPlayerIdxHandIdx(sim, ranks, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    std::cout << "test. IsAceUp(): " << sim->IsAceUp() << std::endl;
    sim->CheckInsuranceAndBlackjack();
    std::cout << "test. chips p0: " << sim->GetPlayerAt(0)->GetChips() << std::endl;
    std::cout << "test. chips p1: " << sim->GetPlayerAt(1)->GetChips() << std::endl;
    testPassed &= 25 == sim->GetPlayerAt(0)->GetChips();
    testPassed &= 0  == sim->GetPlayerAt(1)->GetChips();


    return testPassed;
}
