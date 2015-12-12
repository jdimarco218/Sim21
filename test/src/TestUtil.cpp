#include <assert.h>
#include <iostream>
#include <list>
#include <memory>
#include <vector>
#include "Sim.h"
#include "Card.h"
#include "Deck.h"
#include "Shoe.h"

void ResetTestEnv(std::unique_ptr<Sim>& sim)
{

    // Reset chips to zero, clear hands, clear bets
    for (auto& player : sim->GetPlayersVec())
    {
        player->ResetPlayer();
        player->SetChips(0);    
    }
    sim->GetDealer()->ResetPlayer();

    return;
}

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

