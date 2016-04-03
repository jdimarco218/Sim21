#include <assert.h>
#include <iostream>
#include <list>
#include <memory>
#include <vector>
#include "Sim.h"
#include "Card.h"
#include "Deck.h"
#include "Shoe.h"

/**
 * Reset the test environment by clearing hands, bets, and re-initializing chips
 */
void ResetTestEnv(std::unique_ptr<Sim>& sim)
{
    sim->GetGame() = std::unique_ptr<Game>(new Game(sim->GetGame()->GetDeckType()));
    
    // Reset chips to zero, clear hands, clear bets
    //
    for (auto& player : sim->GetPlayersVec())
    {
        player->ResetPlayer();
        player->SetChips(0);    
    }
    sim->GetDealer()->ResetPlayer();

    return;
}

/**
 * Sets the front of the Shoe to the given Card ranks
 */
void FrontloadShoe(std::unique_ptr<Sim>& sim, std::vector<int> ranks)
{
    auto& shoeCards = sim->GetGame()->GetShoe()->GetCards();
    for (auto it = ranks.rbegin(); it != ranks.rend(); it++)
    {
        // Use 1 as the default suit
        shoeCards.push_front(std::unique_ptr<Card>(new Card(*it, 1)));
    }
    return;
}

/**
 * Sets the front of the Shoe to the given Card ranks and suits
 */
void FrontloadShoe(std::unique_ptr<Sim>& sim, std::vector<std::pair<int, int> > ranks)
{
    auto& shoeCards = sim->GetGame()->GetShoe()->GetCards();
    for (auto it = ranks.rbegin(); it != ranks.rend(); it++)
    {
        shoeCards.push_front(std::unique_ptr<Card>(new Card(it->first, it->second)));
    }
    return;
}

/**
 * Helper function to create a player's specific hand given a set of ranks
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

/**
 * Helper function to create a player's specific hand given a set of ranks and suits
 */
void MakeHandForPlayerIdxHandIdx(std::unique_ptr<Sim>& sim, std::vector<std::pair<int, int> > ranks, int pIdx, int hIdx)
{

    // Assert this is a new or existing hand
    assert(sim->GetPlayerAt(pIdx)->GetHands().size() >= hIdx && "Must be a new or existing hand index!");

    // Insert the hand at the correct index
    if(sim->GetPlayerAt(pIdx)->GetHands().size() == hIdx)
    {
        // New hand, populate a new one
        std::vector<std::unique_ptr<Card> > hand;
        hand.clear();

        for (auto it = ranks.begin(); it != ranks.end(); it++)
        {
            hand.push_back(std::unique_ptr<Card>(new Card(it->first, it->second)));
        }

        sim->GetPlayerAt(pIdx)->GetHands().push_back(std::move(hand));
    }
    else
    {
        // Existing hand, update it
        std::vector<std::unique_ptr<Card> >& hand = sim->GetPlayerAt(pIdx)->GetHand(hIdx);
        hand.clear();

        for (auto it = ranks.begin(); it != ranks.end(); it++)
        {
            hand.push_back(std::unique_ptr<Card>(new Card(it->first, it->second)));
        }
    }

    return;
}

/**
 * Helper function to create a dealer's specific hand given a set of ranks
 */
void MakeHandForDealer(std::unique_ptr<Sim>& sim, std::vector<int> ranks)
{
    // If dealer has a hand already, clear it
    assert(sim->GetDealer()->GetHands().size() == 1 && "Dealer must have one hand during InsuranceTest()");

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
 * Helper function to create a dealer's specific hand given a set of ranks and suits
 */
void MakeHandForDealer(std::unique_ptr<Sim>& sim, std::vector<std::pair<int, int> > ranks)
{
    // If dealer has a hand already, clear it
    assert(sim->GetDealer()->GetHands().size() == 1 && "Dealer must have one hand during InsuranceTest()");

    // Insert the hand at the zero'th index
    std::vector<std::unique_ptr<Card> >& hand = sim->GetDealer()->GetHand(0);
    hand.clear();

        for (auto it = ranks.begin(); it != ranks.end(); it++)
    {
        // All suited as "1", who cares?
        hand.push_back(std::unique_ptr<Card>(new Card(it->first, it->second)));
    }

    return;
}

/**
 * Helper function to set the size of the the remaining Cards in the Shoe.
 * NOTE: FrontloadShoe() if you want to DealCard()s.
 */
void SetShoeToNumCards(std::unique_ptr<Sim>& sim, int numCards)
{
    sim->GetGame()->GetShoe()->GetCards().clear();
    for (int i = 0; i < numCards; ++i)
    {
        sim->GetGame()->GetShoe()->GetCards().push_back(std::unique_ptr<Card>(new Card(0, 1)));
    }
    return;
}

/**
 * Helper function to set the current Hilo count of the Shoe regardless of what
 * has already been dealt.
 */
void SetHiloCount(std::unique_ptr<Sim>& sim, int count)
{
    // Deal the appropriate value Hilo cards until we reach the desired count
    //
    std::vector<int> ranks;
    while (sim->GetGame()->GetHiloCount() < count)
    {
        // Raise count
        ranks.push_back(6);
        FrontloadShoe(sim, ranks);
        sim->GetGame()->DealCard();
        ranks.clear();
    }
    while (sim->GetGame()->GetHiloCount() > count)
    {
        // Lower count
        ranks.push_back(10);
        FrontloadShoe(sim, ranks);
        sim->GetGame()->DealCard();
        ranks.clear();
    }
    return;
}

/**
 * Helper function to increase the size of the Shoe to a given number of cards.
 * This is useful to guarantee a clean True Count calculation.
 */
void BackloadShoeToNumCards(std::unique_ptr<Sim>& sim, int totalCards)
{
    if (sim->GetGame()->GetCardsRemaining() > totalCards)
    {
        std::cout << "ERROR: Shoe too large to BackloadShoeToNumCards()"
                  << std::endl;
                  std::cout << sim->GetGame()->GetCardsRemaining()
                  << std::endl;
    }

    auto& shoeCards = sim->GetGame()->GetShoe()->GetCards();
    while (sim->GetGame()->GetCardsRemaining() < totalCards)
    {
        shoeCards.push_back(std::unique_ptr<Card>(new Card(1, 1)));
    }
}

void PrintFirstTenCards(std::unique_ptr<Sim>& sim)
{
    auto& shoeCards = sim->GetGame()->GetShoe()->GetCards();
    int i = 0;
    for (int i = 0; i < 10; ++i)
    {
        std::cout << *shoeCards[i] << ", ";
    }
    std::cout << std::endl;

}
