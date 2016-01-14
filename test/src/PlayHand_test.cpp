#include <assert.h>
#include <iostream>
#include <list>
#include <memory>
#include <vector>
#include "Sim.h"
#include "Card.h"
#include "Deck.h"
#include "Shoe.h"

#include "PlayHand_test.h"
#include "TestUtil.h"

#define DEBUG false

//******************************************************************************
//
// Tests:
//
// The PlayHand() method does a lot. The tests are broken down into the
// following subsections, which should be referred to individually for test
// cases. NOTE, basic strategy is followed for these tests.
//
// Player Splits - refer to PlayHandSplitTest() for permutations
// Player Doubles - refer to PlayHandDoubleTest() for permutations
// Player Hits - refer to PlayHandHitTest() for permutations
// Player Stands - refer to PlayHandStandTest() for permutations
// Player Surrenders - refer to PlayHandSurrenderTest() for permutations
//
//******************************************************************************

/**
 * This test acts as a wrapper for the child tests. As a whole, it aims to test
 * the Sim::PlayHand() method
 */
bool PlayHandTest(std::unique_ptr<Sim>& sim, bool verbose)
{
    bool testPassed = true;

    testPassed &= PlayHandSplitTest(sim, verbose);
    testPassed &= PlayHandDoubleTest(sim, verbose);
    testPassed &= PlayHandHitTest(sim, verbose);
    testPassed &= PlayHandStandTest(sim, verbose);
    testPassed &= PlayHandSurrenderTest(sim, verbose);

    return testPassed;
}

//******************************************************************************
//
// Player Splits Tests:
//
// When a player Splits, TODO
//
// Standard splits then hits
// Standard splits then doubles
// Maximum splits, follow-up action wins and losses
// Maximum splits, follow-up action surrender(s), push(es), win, and loss
// Aces tests
//   -Dealer bj no play
//   -No  resplit,  no play,  no bonus, bj win, win, push, loss
//   -No  resplit,  no play, yes bonus, bj win, win, push, loss
//   -No  resplit, yes play, yes bonus, bj win, win, push, loss
//   -Yes resplit, yes play, yes bonus, bj win, win, push, loss
//   -Yes resplit, yes play,  no bonus, bj win, win, push, loss
//   -Yes resplit,  no play,  no bonus, bj win, win, push, loss
//
// TODO
//
//******************************************************************************

/**
 * This tests the Split action of Sim::PlayHand()
 */
bool PlayHandSplitTest(std::unique_ptr<Sim>& sim, bool verbose)
{
    bool testPassed = true;
    bool preTest = true;
    int  prevNumSplits = sim->GetGame()->GetNumSplits();
    bool prevResplitAces = sim->GetGame()->GetResplitAces();
    bool prevPlaySplitAces = sim->GetGame()->GetPlaySplitAces();
    bool prevBonusPayOnSplitAces = sim->GetGame()->GetBonusPayOnSplitAces();

    std::vector<int> ranks0;
    std::vector<int> ranks1;
    std::vector<int> shoeRanks;
    std::vector<int> dealerRanks;
    std::string ref = "";
    int refCount = 0;
    sim->GetPlayerAt(0)->SetDeviating(false);
    sim->GetPlayerAt(1)->SetDeviating(false);

    // TEST CASE
    // Both players split 7s
    // Player 0 wins both
    // Player 1 loses both
    //
    ResetTestEnv(sim);
    ref = "PlayHandSplitTest " + std::to_string(refCount++);
    preTest = testPassed;
    ranks0.clear();
    ranks1.clear();
    dealerRanks.clear();
    shoeRanks.clear();
    ranks0.push_back(7);
    ranks0.push_back(7); // player0 p7
    ranks1.push_back(7);
    ranks1.push_back(7); // player1 p7
    shoeRanks.push_back(8); // player0 gets 15
    shoeRanks.push_back(6); // player0 gets 21 on first hand
    shoeRanks.push_back(6); // player0 gets 13
    shoeRanks.push_back(7); // player0 gets 21 on second hand
    shoeRanks.push_back(13); // player1 gets 17 on first hand
    shoeRanks.push_back(9); // player1 gets 16
    shoeRanks.push_back(9); // player1 busts on second hand
    dealerRanks.push_back(7);
    dealerRanks.push_back(1); // dealer 18, with 7 Up 
    MakeHandForPlayerIdxHandIdx(sim, ranks0, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks1, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    FrontloadShoe(sim, shoeRanks);
    sim->CheckInsuranceAndBlackjack();
    sim->PlayHand(0, 0);
    sim->PlayHand(1, 0);
    sim->PlayDealerHand();
    sim->PayoutWinners();
    testPassed &=  50 == sim->GetPlayerAt(0)->GetChips();
    testPassed &= -50 == sim->GetPlayerAt(1)->GetChips();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // Both players split 9s then double afterwards
    // Player 0 wins both
    // Player 1 loses both
    //
    ResetTestEnv(sim);
    ref = "PlayHandSplitTest " + std::to_string(refCount++);
    preTest = testPassed;
    ranks0.clear();
    ranks1.clear();
    dealerRanks.clear();
    shoeRanks.clear();
    ranks0.push_back(9);
    ranks0.push_back(9); // player0 p9
    ranks1.push_back(9);
    ranks1.push_back(9); // player1 p9
    shoeRanks.push_back(2); // player0 gets 11
    shoeRanks.push_back(9); // player0 doubles to 20 on first hand
    shoeRanks.push_back(2); // player0 gets 11
    shoeRanks.push_back(11); // player0 gets 21 on second hand
    shoeRanks.push_back(2); // player1 gets 11
    shoeRanks.push_back(5); // player1 gets 16 on first hand, shouldn't hit
    shoeRanks.push_back(2); // player1 gets 11
    shoeRanks.push_back(6); // player1 gets 17 on second hand
    dealerRanks.push_back(8);
    dealerRanks.push_back(11); // dealer 18, with 8 Up 
    MakeHandForPlayerIdxHandIdx(sim, ranks0, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks1, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    FrontloadShoe(sim, shoeRanks);
    sim->CheckInsuranceAndBlackjack();
    sim->PlayHand(0, 0);
    sim->PlayHand(1, 0);
    sim->PlayDealerHand();
    sim->PayoutWinners();
    testPassed &=  100 == sim->GetPlayerAt(0)->GetChips();
    testPassed &= -100 == sim->GetPlayerAt(1)->GetChips();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // Both players split 8s up to the max splits
    // Player 0 wins all
    // Player 1 loses all
    //
    ResetTestEnv(sim);
    ref = "PlayHandSplitTest " + std::to_string(refCount++);
    preTest = testPassed;
    sim->GetGame()->SetNumSplits(3); // 3 max splits for this test
    ranks0.clear();
    ranks1.clear();
    dealerRanks.clear();
    shoeRanks.clear();
    ranks0.push_back(8);
    ranks0.push_back(8); // player0 p8
    ranks1.push_back(8);
    ranks1.push_back(8); // player1 p8
    shoeRanks.push_back(8); // player0 gets another p8
    shoeRanks.push_back(8); // player0 gets a 3rd p8 and takes follow-up
    shoeRanks.push_back(5); // player0 gets 21 on first hand
    shoeRanks.push_back(1); // player0 gets s19 on second hand
    shoeRanks.push_back(8); // player0 gets another p8 and takes another follow
    shoeRanks.push_back(4); // player0 gets 20 on third hand
    shoeRanks.push_back(8); // player1 gets another p8
    shoeRanks.push_back(8); // player1 gets a 3rd p8 and takes follow-up
    shoeRanks.push_back(13); // player1 busts on first hand
    shoeRanks.push_back(9); // player1 gets 17 on second hand
    shoeRanks.push_back(8); // player1 gets p8 and takes another follow-up
    shoeRanks.push_back(1); // player1 gets s17
    dealerRanks.push_back(8);
    dealerRanks.push_back(7); // dealer 15, with 8 Up 
    shoeRanks.push_back(3); // dealer gets 18
    MakeHandForPlayerIdxHandIdx(sim, ranks0, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks1, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    FrontloadShoe(sim, shoeRanks);
    sim->CheckInsuranceAndBlackjack();
    sim->PlayHand(0, 0);
    sim->PlayHand(1, 0);
    sim->PlayDealerHand();
    sim->PayoutWinners();
    testPassed &=  75 == sim->GetPlayerAt(0)->GetChips();
    testPassed &= -75 == sim->GetPlayerAt(1)->GetChips();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}
    sim->GetGame()->SetNumSplits(prevNumSplits); // revert numSplits

    // TEST CASE
    // Both players split 8s up to the max splits
    // Player 0 wins 1, surrenders one, pushes one
    // Player 1 loses 1, surrenders one, pushes one
    //
    ResetTestEnv(sim);
    ref = "PlayHandSplitTest " + std::to_string(refCount++);
    if(DEBUG) {std::cout << "Starting " << ref << std::endl;}
    preTest = testPassed;
    sim->GetGame()->SetNumSplits(3); // 3 max splits for this test
    ranks0.clear();
    ranks1.clear();
    dealerRanks.clear();
    shoeRanks.clear();
    ranks0.push_back(8);
    ranks0.push_back(8); // player0 p8
    ranks1.push_back(8);
    ranks1.push_back(8); // player1 p8
    shoeRanks.push_back(8); // player0 gets another p8
    shoeRanks.push_back(8); // player0 gets a 3rd p8 and takes follow up Sur.
    shoeRanks.push_back(5); // player0 gets 13
    shoeRanks.push_back(3); // player0 gets 16
    shoeRanks.push_back(5); // player0 gets 21 on second hand
    shoeRanks.push_back(1); // player0 gets s19 on third hand
    shoeRanks.push_back(8); // player1 gets another p8
    shoeRanks.push_back(5); // player1 gets 13
    shoeRanks.push_back(10); // player1 busts first hand
    shoeRanks.push_back(8); // player1 gets a 3rd p8 and takes follow-up
    shoeRanks.push_back(1); // player1 gets s19 for push
    dealerRanks.push_back(10);
    dealerRanks.push_back(9); // dealer 19, with T Up 
    MakeHandForPlayerIdxHandIdx(sim, ranks0, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks1, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    FrontloadShoe(sim, shoeRanks);
    sim->CheckInsuranceAndBlackjack();
    sim->PlayHand(0, 0);
    sim->PlayHand(1, 0);
    sim->PlayDealerHand();
    sim->PayoutWinners();
    testPassed &=  12.5 == sim->GetPlayerAt(0)->GetChips();
    testPassed &= -37.5 == sim->GetPlayerAt(1)->GetChips();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}
    sim->GetGame()->SetNumSplits(prevNumSplits); // revert numSplits
    
    // TEST CASE
    // Test no resplit, no play, no bonus
    // Dealer blackjack so no splits
    //
    ResetTestEnv(sim);
    ref = "PlayHandSplitTest " + std::to_string(refCount++);
    preTest = testPassed;
    sim->GetGame()->SetNumSplits(4); // Set rules for this test
    sim->GetGame()->SetResplitAces(false);
    sim->GetGame()->SetPlaySplitAces(false);
    sim->GetGame()->SetBonusPayOnSplitAces(false);
    ranks0.clear();
    ranks1.clear();
    dealerRanks.clear();
    shoeRanks.clear();
    ranks0.push_back(1);
    ranks0.push_back(1); // player0 pA
    ranks1.push_back(1);
    ranks1.push_back(1); // player1 pA
    dealerRanks.push_back(10);
    dealerRanks.push_back(1); // dealer 18, with T Up 
    MakeHandForPlayerIdxHandIdx(sim, ranks0, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks1, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    FrontloadShoe(sim, shoeRanks);
    sim->CheckInsuranceAndBlackjack();
    // Players should be inactive now
    //
    for (int i = 0; i < sim->GetPlayersVec().size(); ++i)
    {
        if (sim->GetPlayerAt(i)->IsActiveAt(0))
        {
            sim->PlayHand(i, 0);
        }
    }
    sim->PlayDealerHand();
    sim->PayoutWinners();
    testPassed &= -25.0 == sim->GetPlayerAt(0)->GetChips();
    testPassed &= -25.0 == sim->GetPlayerAt(1)->GetChips();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}
    sim->GetGame()->SetNumSplits(prevNumSplits); // revert numSplits
    sim->GetGame()->SetResplitAces(prevResplitAces); // revert resplitAces
    sim->GetGame()->SetPlaySplitAces(prevPlaySplitAces); // revert play split
    sim->GetGame()->SetBonusPayOnSplitAces(prevBonusPayOnSplitAces); // revert

    // TEST CASE
    // Test no resplit, no play, no bonus
    // Player 0 wins one blackjack, standard wins other
    // Player 1 pushes one, loses other
    //
    ResetTestEnv(sim);
    ref = "PlayHandSplitTest " + std::to_string(refCount++);
    preTest = testPassed;
    sim->GetGame()->SetNumSplits(4); // Set rules for this test
    sim->GetGame()->SetResplitAces(false);
    sim->GetGame()->SetPlaySplitAces(false);
    sim->GetGame()->SetBonusPayOnSplitAces(false);
    ranks0.clear();
    ranks1.clear();
    dealerRanks.clear();
    shoeRanks.clear();
    ranks0.push_back(1);
    ranks0.push_back(1); // player0 pA
    ranks1.push_back(1);
    ranks1.push_back(1); // player1 pA
    shoeRanks.push_back(10); // player0 gets blackjack on first hand
    shoeRanks.push_back(9); // player0 gets s20 on second hand
    shoeRanks.push_back(7); // player1 gets 18 on first hand
    shoeRanks.push_back(5); // player0 gets 12 on second hand
    shoeRanks.push_back(9); // should not be a dealt card
    dealerRanks.push_back(10);
    dealerRanks.push_back(8); // dealer 18, with T Up 
    MakeHandForPlayerIdxHandIdx(sim, ranks0, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks1, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    FrontloadShoe(sim, shoeRanks);
    sim->CheckInsuranceAndBlackjack();
    sim->PlayHand(0, 0);
    sim->PlayHand(1, 0);
    sim->PlayDealerHand();
    sim->PayoutWinners();
    testPassed &=  50.0 == sim->GetPlayerAt(0)->GetChips();
    testPassed &= -25.0 == sim->GetPlayerAt(1)->GetChips();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}
    sim->GetGame()->SetNumSplits(prevNumSplits); // revert numSplits
    sim->GetGame()->SetResplitAces(prevResplitAces); // revert resplitAces
    sim->GetGame()->SetPlaySplitAces(prevPlaySplitAces); // revert play split
    sim->GetGame()->SetBonusPayOnSplitAces(prevBonusPayOnSplitAces); // revert

    // TEST CASE
    // Test no resplit, no play, yes bonus
    // Player 0 wins one blackjack, standard wins other
    // Player 1 pushes one, loses other
    //
    ResetTestEnv(sim);
    ref = "PlayHandSplitTest " + std::to_string(refCount++);
    preTest = testPassed;
    sim->GetGame()->SetNumSplits(4); // Set rules for this test
    sim->GetGame()->SetResplitAces(false);
    sim->GetGame()->SetPlaySplitAces(false);
    sim->GetGame()->SetBonusPayOnSplitAces(true);
    ranks0.clear();
    ranks1.clear();
    dealerRanks.clear();
    shoeRanks.clear();
    ranks0.push_back(1);
    ranks0.push_back(1); // player0 pA
    ranks1.push_back(1);
    ranks1.push_back(1); // player1 pA
    shoeRanks.push_back(10); // player0 gets blackjack on first hand
    shoeRanks.push_back(9); // player0 gets s20 on second hand
    shoeRanks.push_back(7); // player1 gets 18 on first hand
    shoeRanks.push_back(5); // player0 gets 12 on second hand
    shoeRanks.push_back(9); // should not be a dealt card
    dealerRanks.push_back(10);
    dealerRanks.push_back(8); // dealer 18, with T Up 
    MakeHandForPlayerIdxHandIdx(sim, ranks0, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks1, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    FrontloadShoe(sim, shoeRanks);
    sim->CheckInsuranceAndBlackjack();
    sim->PlayHand(0, 0);
    sim->PlayHand(1, 0);
    sim->PlayDealerHand();
    sim->PayoutWinners();
    testPassed &=  62.5 == sim->GetPlayerAt(0)->GetChips();
    testPassed &= -25.0 == sim->GetPlayerAt(1)->GetChips();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}
    sim->GetGame()->SetNumSplits(prevNumSplits); // revert numSplits
    sim->GetGame()->SetResplitAces(prevResplitAces); // revert resplitAces
    sim->GetGame()->SetPlaySplitAces(prevPlaySplitAces); // revert play split
    sim->GetGame()->SetBonusPayOnSplitAces(prevBonusPayOnSplitAces); // revert

    // TEST CASE
    // Test no resplit, yes play, yes bonus
    // Player 0 wins one blackjack, standard wins other
    // Player 1 pushes one, loses other
    //
    ResetTestEnv(sim);
    ref = "PlayHandSplitTest " + std::to_string(refCount++);
    preTest = testPassed;
    sim->GetGame()->SetNumSplits(4); // Set rules for this test
    sim->GetGame()->SetResplitAces(false);
    sim->GetGame()->SetPlaySplitAces(true);
    sim->GetGame()->SetBonusPayOnSplitAces(true);
    ranks0.clear();
    ranks1.clear();
    dealerRanks.clear();
    shoeRanks.clear();
    ranks0.push_back(1);
    ranks0.push_back(1); // player0 pA
    ranks1.push_back(1);
    ranks1.push_back(1); // player1 pA
    shoeRanks.push_back(10); // player0 gets blackjack on first hand
    shoeRanks.push_back(7); // player0 gets s18
    shoeRanks.push_back(2); // player0 gets s20 on second hand
    shoeRanks.push_back(7); // player1 gets s18
    shoeRanks.push_back(12); // player1 gets 18 on first hand
    shoeRanks.push_back(5); // player1 gets s16
    shoeRanks.push_back(10); // player1 gets 16
    shoeRanks.push_back(11); // player1 busts on second hand
    dealerRanks.push_back(10);
    dealerRanks.push_back(8); // dealer 18, with T Up 
    MakeHandForPlayerIdxHandIdx(sim, ranks0, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks1, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    FrontloadShoe(sim, shoeRanks);
    sim->CheckInsuranceAndBlackjack();
    sim->PlayHand(0, 0);
    sim->PlayHand(1, 0);
    sim->PlayDealerHand();
    sim->PayoutWinners();
    testPassed &=  62.5 == sim->GetPlayerAt(0)->GetChips();
    testPassed &= -25.0 == sim->GetPlayerAt(1)->GetChips();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}
    sim->GetGame()->SetNumSplits(prevNumSplits); // revert numSplits
    sim->GetGame()->SetResplitAces(prevResplitAces); // revert resplitAces
    sim->GetGame()->SetPlaySplitAces(prevPlaySplitAces); // revert play split
    sim->GetGame()->SetBonusPayOnSplitAces(prevBonusPayOnSplitAces); // revert

    // TEST CASE
    // Test yes resplit, yes play, yes bonus
    // Player 0 wins one blackjack, standard wins others
    // Player 1 pushes one, loses others
    //
    ResetTestEnv(sim);
    ref = "PlayHandSplitTest " + std::to_string(refCount++);
    preTest = testPassed;
    sim->GetGame()->SetNumSplits(3); // Set rules for this test
    sim->GetGame()->SetResplitAces(true);
    sim->GetGame()->SetPlaySplitAces(true);
    sim->GetGame()->SetBonusPayOnSplitAces(true);
    ranks0.clear();
    ranks1.clear();
    dealerRanks.clear();
    shoeRanks.clear();
    ranks0.push_back(1);
    ranks0.push_back(1); // player0 pA
    ranks1.push_back(1);
    ranks1.push_back(1); // player1 pA
    shoeRanks.push_back(1); // player0 gets another pA
    shoeRanks.push_back(11); // player0 gets blackjack on first hand
    shoeRanks.push_back(1); // player0 gets pA, follow-up
    shoeRanks.push_back(8); // player0 gets s20 on second hand
    shoeRanks.push_back(9); // player0 gets s20 on third hand
    shoeRanks.push_back(1); // player1 gets another pA
    shoeRanks.push_back(7); // player1 gets s18
    shoeRanks.push_back(10); // player1 gets 18 on first hand
    shoeRanks.push_back(1); // player1 gets pA, follow-up
    shoeRanks.push_back(12); // player1 gets 12
    shoeRanks.push_back(12); // player1 busts on second hand
    shoeRanks.push_back(5); // player1 gets s16
    shoeRanks.push_back(10); // player1 gets 16
    shoeRanks.push_back(11); // player1 busts on third hand
    dealerRanks.push_back(10);
    dealerRanks.push_back(8); // dealer 18, with T Up 
    MakeHandForPlayerIdxHandIdx(sim, ranks0, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks1, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    FrontloadShoe(sim, shoeRanks);
    sim->CheckInsuranceAndBlackjack();
    sim->PlayHand(0, 0);
    sim->PlayHand(1, 0);
    sim->PlayDealerHand();
    sim->PayoutWinners();
    testPassed &=  87.5 == sim->GetPlayerAt(0)->GetChips();
    testPassed &= -50.0 == sim->GetPlayerAt(1)->GetChips();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}
    sim->GetGame()->SetNumSplits(prevNumSplits); // revert numSplits
    sim->GetGame()->SetResplitAces(prevResplitAces); // revert resplitAces
    sim->GetGame()->SetPlaySplitAces(prevPlaySplitAces); // revert play split
    sim->GetGame()->SetBonusPayOnSplitAces(prevBonusPayOnSplitAces); // revert

    // TEST CASE
    // Test yes resplit, yes play, no bonus
    // Player 0 wins one blackjack, standard wins others
    // Player 1 pushes one, loses others
    //
    ResetTestEnv(sim);
    ref = "PlayHandSplitTest " + std::to_string(refCount++);
    preTest = testPassed;
    sim->GetGame()->SetNumSplits(3); // Set rules for this test
    sim->GetGame()->SetResplitAces(true);
    sim->GetGame()->SetPlaySplitAces(true);
    sim->GetGame()->SetBonusPayOnSplitAces(false);
    ranks0.clear();
    ranks1.clear();
    dealerRanks.clear();
    shoeRanks.clear();
    ranks0.push_back(1);
    ranks0.push_back(1); // player0 pA
    ranks1.push_back(1);
    ranks1.push_back(1); // player1 pA
    shoeRanks.push_back(1); // player0 gets another pA
    shoeRanks.push_back(11); // player0 gets blackjack on first hand
    shoeRanks.push_back(1); // player0 gets pA, follow-up
    shoeRanks.push_back(8); // player0 gets s20 on second hand
    shoeRanks.push_back(9); // player0 gets s20 on third hand
    shoeRanks.push_back(1); // player1 gets another pA
    shoeRanks.push_back(7); // player1 gets s18
    shoeRanks.push_back(10); // player1 gets 18 on first hand
    shoeRanks.push_back(1); // player1 gets pA, follow-up
    shoeRanks.push_back(12); // player1 gets 12
    shoeRanks.push_back(12); // player1 busts on second hand
    shoeRanks.push_back(5); // player1 gets s16
    shoeRanks.push_back(10); // player1 gets 16
    shoeRanks.push_back(11); // player1 busts on third hand
    dealerRanks.push_back(10);
    dealerRanks.push_back(8); // dealer 18, with T Up 
    MakeHandForPlayerIdxHandIdx(sim, ranks0, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks1, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    FrontloadShoe(sim, shoeRanks);
    sim->CheckInsuranceAndBlackjack();
    sim->PlayHand(0, 0);
    sim->PlayHand(1, 0);
    sim->PlayDealerHand();
    sim->PayoutWinners();
    testPassed &=  75.0 == sim->GetPlayerAt(0)->GetChips();
    testPassed &= -50.0 == sim->GetPlayerAt(1)->GetChips();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}
    sim->GetGame()->SetNumSplits(prevNumSplits); // revert numSplits
    sim->GetGame()->SetResplitAces(prevResplitAces); // revert resplitAces
    sim->GetGame()->SetPlaySplitAces(prevPlaySplitAces); // revert play split
    sim->GetGame()->SetBonusPayOnSplitAces(prevBonusPayOnSplitAces); // revert

    // TEST CASE
    // Test yes resplit, no play, no bonus
    // Player 0 wins one blackjack, one push
    // Player 1 pushes one, loses others
    //
    ResetTestEnv(sim);
    ref = "PlayHandSplitTest " + std::to_string(refCount++);
    preTest = testPassed;
    sim->GetGame()->SetNumSplits(3); // Set rules for this test
    sim->GetGame()->SetResplitAces(true);
    sim->GetGame()->SetPlaySplitAces(false);
    sim->GetGame()->SetBonusPayOnSplitAces(false);
    ranks0.clear();
    ranks1.clear();
    dealerRanks.clear();
    shoeRanks.clear();
    ranks0.push_back(1);
    ranks0.push_back(1); // player0 pA
    ranks1.push_back(1);
    ranks1.push_back(1); // player1 pA
    shoeRanks.push_back(10); // player0 gets blackjack on first hand
    shoeRanks.push_back(7); // player0 gets s18 on third hand
    shoeRanks.push_back(1); // player1 gets s12 on first hand
    shoeRanks.push_back(7); // player1 gets s18 on second hand
    shoeRanks.push_back(10); // should not be dealt
    dealerRanks.push_back(10);
    dealerRanks.push_back(8); // dealer 18, with T Up 
    MakeHandForPlayerIdxHandIdx(sim, ranks0, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks1, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    FrontloadShoe(sim, shoeRanks);
    sim->CheckInsuranceAndBlackjack();
    sim->PlayHand(0, 0);
    sim->PlayHand(1, 0);
    sim->PlayDealerHand();
    sim->PayoutWinners();
    testPassed &=  25.0 == sim->GetPlayerAt(0)->GetChips();
    testPassed &= -25.0 == sim->GetPlayerAt(1)->GetChips();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}
    sim->GetGame()->SetNumSplits(prevNumSplits); // revert numSplits
    sim->GetGame()->SetResplitAces(prevResplitAces); // revert resplitAces
    sim->GetGame()->SetPlaySplitAces(prevPlaySplitAces); // revert play split
    sim->GetGame()->SetBonusPayOnSplitAces(prevBonusPayOnSplitAces); // revert

    // TEST CASE
    // TC +3
    // Both players split 9s then double afterwards
    // Player 0 wins both
    // Player 1 loses both
    //
    ResetTestEnv(sim);
    ref = "PlayHandSplitTest " + std::to_string(refCount++);
    preTest = testPassed;
    sim->GetPlayerAt(0)->SetCounting(true); // Set players to count
    sim->GetPlayerAt(1)->SetCounting(true);
    ranks0.clear();
    ranks1.clear();
    dealerRanks.clear();
    shoeRanks.clear();
    ranks0.push_back(9);
    ranks0.push_back(9); // player0 p9
    ranks1.push_back(9);
    ranks1.push_back(9); // player1 p9
    shoeRanks.push_back(2); // player0 gets 11
    shoeRanks.push_back(9); // player0 doubles to 20 on first hand
    shoeRanks.push_back(2); // player0 gets 11
    shoeRanks.push_back(11); // player0 gets 21 on second hand
    shoeRanks.push_back(2); // player1 gets 11
    shoeRanks.push_back(5); // player1 gets 16 on first hand, shouldn't hit
    shoeRanks.push_back(2); // player1 gets 11
    shoeRanks.push_back(6); // player1 gets 17 on second hand
    dealerRanks.push_back(8);
    dealerRanks.push_back(11); // dealer 18, with 8 Up 
    MakeHandForPlayerIdxHandIdx(sim, ranks0, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks1, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    FrontloadShoe(sim, shoeRanks);
    SetHiloCount(sim, 24);
    BackloadShoeToNumCards(sim, 416); // RC 24 / 8 decks = TC +3
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    sim->CheckInsuranceAndBlackjack();
    sim->PlayHand(0, 0);
    sim->PlayHand(1, 0);
    sim->PlayDealerHand();
    sim->PayoutWinners();
    testPassed &=  400 == sim->GetPlayerAt(0)->GetChips();
    testPassed &= -400 == sim->GetPlayerAt(1)->GetChips();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // TC +3
    // Test yes resplit, yes play, no bonus
    // Player 0 wins one blackjack, standard wins others
    // Player 1 pushes one, loses others
    //
    ResetTestEnv(sim);
    ref = "PlayHandSplitTest " + std::to_string(refCount++);
    preTest = testPassed;
    sim->GetPlayerAt(0)->SetCounting(true); // Set players to count
    sim->GetPlayerAt(1)->SetCounting(true);
    sim->GetGame()->SetNumSplits(3); // Set rules for this test
    sim->GetGame()->SetResplitAces(true);
    sim->GetGame()->SetPlaySplitAces(true);
    sim->GetGame()->SetBonusPayOnSplitAces(false);
    ranks0.clear();
    ranks1.clear();
    dealerRanks.clear();
    shoeRanks.clear();
    ranks0.push_back(1);
    ranks0.push_back(1); // player0 pA
    ranks1.push_back(1);
    ranks1.push_back(1); // player1 pA
    shoeRanks.push_back(1); // player0 gets another pA
    shoeRanks.push_back(11); // player0 gets blackjack on first hand
    shoeRanks.push_back(1); // player0 gets pA, follow-up
    shoeRanks.push_back(8); // player0 gets s20 on second hand
    shoeRanks.push_back(9); // player0 gets s20 on third hand
    shoeRanks.push_back(1); // player1 gets another pA
    shoeRanks.push_back(7); // player1 gets s18
    shoeRanks.push_back(10); // player1 gets 18 on first hand
    shoeRanks.push_back(1); // player1 gets pA, follow-up
    shoeRanks.push_back(12); // player1 gets 12
    shoeRanks.push_back(12); // player1 busts on second hand
    shoeRanks.push_back(5); // player1 gets s16
    shoeRanks.push_back(10); // player1 gets 16
    shoeRanks.push_back(11); // player1 busts on third hand
    dealerRanks.push_back(10);
    dealerRanks.push_back(8); // dealer 18, with T Up 
    MakeHandForPlayerIdxHandIdx(sim, ranks0, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks1, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    FrontloadShoe(sim, shoeRanks);
    SetHiloCount(sim, 24);
    BackloadShoeToNumCards(sim, 416); // RC 24 / 8 decks = TC +3
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    sim->CheckInsuranceAndBlackjack();
    sim->PlayHand(0, 0);
    sim->PlayHand(1, 0);
    sim->PlayDealerHand();
    sim->PayoutWinners();
    testPassed &=  300.0 == sim->GetPlayerAt(0)->GetChips();
    testPassed &= -200.0 == sim->GetPlayerAt(1)->GetChips();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}
    sim->GetGame()->SetNumSplits(prevNumSplits); // revert numSplits
    sim->GetGame()->SetResplitAces(prevResplitAces); // revert resplitAces
    sim->GetGame()->SetPlaySplitAces(prevPlaySplitAces); // revert play split
    sim->GetGame()->SetBonusPayOnSplitAces(prevBonusPayOnSplitAces); // revert

    // TEST CASE
    // TC +3
    // Test yes resplit, no play, no bonus
    // Player 0 wins one blackjack, one push
    // Player 1 pushes one, loses others
    //
    ResetTestEnv(sim);
    ref = "PlayHandSplitTest " + std::to_string(refCount++);
    preTest = testPassed;
    sim->GetPlayerAt(0)->SetCounting(true);
    sim->GetPlayerAt(1)->SetCounting(true);
    sim->GetGame()->SetNumSplits(3); // Set rules for this test
    sim->GetGame()->SetResplitAces(true);
    sim->GetGame()->SetPlaySplitAces(false);
    sim->GetGame()->SetBonusPayOnSplitAces(false);
    ranks0.clear();
    ranks1.clear();
    dealerRanks.clear();
    shoeRanks.clear();
    ranks0.push_back(1);
    ranks0.push_back(1); // player0 pA
    ranks1.push_back(1);
    ranks1.push_back(1); // player1 pA
    shoeRanks.push_back(10); // player0 gets blackjack on first hand
    shoeRanks.push_back(7); // player0 gets s18 on third hand
    shoeRanks.push_back(1); // player1 gets s12 on first hand
    shoeRanks.push_back(7); // player1 gets s18 on second hand
    shoeRanks.push_back(10); // should not be dealt
    dealerRanks.push_back(10);
    dealerRanks.push_back(8); // dealer 18, with T Up 
    MakeHandForPlayerIdxHandIdx(sim, ranks0, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks1, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    FrontloadShoe(sim, shoeRanks);
    SetHiloCount(sim, 24);
    BackloadShoeToNumCards(sim, 416); // RC 24 / 8 decks = TC +3
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    sim->CheckInsuranceAndBlackjack();
    sim->PlayHand(0, 0);
    sim->PlayHand(1, 0);
    sim->PlayDealerHand();
    sim->PayoutWinners();
    testPassed &=  100.0 == sim->GetPlayerAt(0)->GetChips();
    testPassed &= -100.0 == sim->GetPlayerAt(1)->GetChips();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}
    sim->GetGame()->SetNumSplits(prevNumSplits); // revert numSplits
    sim->GetGame()->SetResplitAces(prevResplitAces); // revert resplitAces
    sim->GetGame()->SetPlaySplitAces(prevPlaySplitAces); // revert play split
    sim->GetGame()->SetBonusPayOnSplitAces(prevBonusPayOnSplitAces); // revert

    return testPassed;
}

//******************************************************************************
//
// Player Doubles Tests:
//
// When a player Doubles, TODO
//
// Primary double hard hand win, lose
// Primary double soft hand win, lose
// Double after split win, lose
// No double after split win, lose
//
//******************************************************************************

/**
 * This tests the Double action of Sim::PlayHand()
 */
bool PlayHandDoubleTest(std::unique_ptr<Sim>& sim, bool verbose)
{
    bool testPassed = true;
    bool preTest = true;
    int  prevDaS = sim->GetGame()->GetDaS();
    int  prevS17 = sim->GetGame()->GetS17();

    std::vector<int> ranks0;
    std::vector<int> ranks1;
    std::vector<int> shoeRanks;
    std::vector<int> dealerRanks;
    std::string ref = "";
    int refCount = 0;

    // TEST CASE
    // Both players double 11
    // Player 0 wins
    // Player 1 loses
    //
    ResetTestEnv(sim);
    ref = "PlayHandDoubleTest " + std::to_string(refCount++);
    preTest = testPassed;
    ranks0.clear();
    ranks1.clear();
    dealerRanks.clear();
    shoeRanks.clear();
    ranks0.push_back(7);
    ranks0.push_back(4); // player0 11
    ranks1.push_back(5);
    ranks1.push_back(6); // player1 11
    shoeRanks.push_back(9); // player0 gets 20
    shoeRanks.push_back(2); // player1 gets 17 on first hand
    shoeRanks.push_back(8); // should not be dealt
    dealerRanks.push_back(7);
    dealerRanks.push_back(1); // dealer 18, with 7 Up 
    MakeHandForPlayerIdxHandIdx(sim, ranks0, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks1, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    FrontloadShoe(sim, shoeRanks);
    sim->CheckInsuranceAndBlackjack();
    sim->PlayHand(0, 0);
    sim->PlayHand(1, 0);
    sim->PlayDealerHand();
    sim->PayoutWinners();
    testPassed &=  50 == sim->GetPlayerAt(0)->GetChips();
    testPassed &= -50 == sim->GetPlayerAt(1)->GetChips();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // Both players double s18
    // Player 0 wins
    // Player 1 loses
    //
    ResetTestEnv(sim);
    ref = "PlayHandDoubleTest " + std::to_string(refCount++);
    preTest = testPassed;
    sim->GetGame()->SetS17(true);
    ranks0.clear();
    ranks1.clear();
    dealerRanks.clear();
    shoeRanks.clear();
    ranks0.push_back(1);
    ranks0.push_back(7); // player0 11
    ranks1.push_back(7);
    ranks1.push_back(1); // player1 11
    shoeRanks.push_back(2); // player0 gets 20
    shoeRanks.push_back(8); // player1 gets 16 on first hand
    shoeRanks.push_back(8); // should not be dealt
    dealerRanks.push_back(6);
    dealerRanks.push_back(1); // dealer s17
    MakeHandForPlayerIdxHandIdx(sim, ranks0, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks1, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    FrontloadShoe(sim, shoeRanks);
    sim->CheckInsuranceAndBlackjack();
    sim->PlayHand(0, 0);
    sim->PlayHand(1, 0);
    sim->PlayDealerHand();
    sim->PayoutWinners();
    testPassed &=  50 == sim->GetPlayerAt(0)->GetChips();
    testPassed &= -50 == sim->GetPlayerAt(1)->GetChips();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}
    sim->GetGame()->SetS17(prevS17);

    return testPassed;
}

//******************************************************************************
//
// Player Hits Tests:
//
// For each basic strategy of Player:
//
// Primary hit action, hard total
// Primary hit action, soft total
// Secondary hit action, unable to double
// Secondary hit action, soft total - cannot double
// Player busts, dealer busts too
//
//******************************************************************************

/**
 * This tests the Hit action of Sim::PlayHand()
 */
bool PlayHandHitTest(std::unique_ptr<Sim>& sim, bool verbose)
{
    bool testPassed = true;
    bool preTest = true;

    std::vector<int> ranks0;
    std::vector<int> ranks1;
    std::vector<int> shoeRanks;
    std::vector<int> dealerRanks;
    std::string ref = "";
    int refCount = 0;

    // TEST CASE
    // Both players take one primary hard total hit action
    // Player 0 wins
    // Player 1 loses
    //
    ResetTestEnv(sim);
    ref = "PlayHandHitTest " + std::to_string(refCount++);
    preTest = testPassed;
    ranks0.clear();
    ranks1.clear();
    dealerRanks.clear();
    shoeRanks.clear();
    ranks0.push_back(8);
    ranks0.push_back(6); // player0 14
    ranks1.push_back(5);
    ranks1.push_back(3); // player1 8
    shoeRanks.push_back(7); // player0 gets 21
    shoeRanks.push_back(13); // player1 gets 18
    dealerRanks.push_back(10);
    dealerRanks.push_back(10); // dealer 20, with T Up 
    MakeHandForPlayerIdxHandIdx(sim, ranks0, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks1, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    FrontloadShoe(sim, shoeRanks);
    sim->CheckInsuranceAndBlackjack();
    sim->PlayHand(0, 0);
    sim->PlayHand(1, 0);
    sim->PlayDealerHand();
    sim->PayoutWinners();
    testPassed &=  25 == sim->GetPlayerAt(0)->GetChips();
    testPassed &= -25 == sim->GetPlayerAt(1)->GetChips();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // Both players take one primary soft total hit action
    // Player 0 wins
    // Player 1 loses
    //
    ResetTestEnv(sim);
    ref = "PlayHandHitTest " + std::to_string(refCount++);
    preTest = testPassed;
    ranks0.clear();
    ranks1.clear();
    dealerRanks.clear();
    shoeRanks.clear();
    ranks0.push_back(1);
    ranks0.push_back(3); // player0 s14
    ranks1.push_back(1);
    ranks1.push_back(7); // player1 s18
    shoeRanks.push_back(7); // player0 gets 21
    shoeRanks.push_back(1); // player1 gets s19
    dealerRanks.push_back(10);
    dealerRanks.push_back(10); // dealer 20, with T Up 
    MakeHandForPlayerIdxHandIdx(sim, ranks0, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks1, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    FrontloadShoe(sim, shoeRanks);
    sim->CheckInsuranceAndBlackjack();
    sim->PlayHand(0, 0);
    sim->PlayHand(1, 0);
    sim->PlayDealerHand();
    sim->PayoutWinners();
    testPassed &=  25 == sim->GetPlayerAt(0)->GetChips();
    testPassed &= -25 == sim->GetPlayerAt(1)->GetChips();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // Both players take one secondary hard total hit action
    // Player 0 wins
    // Player 1 loses
    //
    ResetTestEnv(sim);
    ref = "PlayHandHitTest " + std::to_string(refCount++);
    preTest = testPassed;
    ranks0.clear();
    ranks1.clear();
    dealerRanks.clear();
    shoeRanks.clear();
    ranks0.push_back(2);
    ranks0.push_back(2);
    ranks0.push_back(7); // player0 three card 11
    ranks1.push_back(5);
    ranks1.push_back(2);
    ranks1.push_back(4); // player1 three card 11
    shoeRanks.push_back(5); // player0 gets 15, hits again
    shoeRanks.push_back(4); // player0 gets 20
    shoeRanks.push_back(6); // player1 gets 16, hits again
    shoeRanks.push_back(12); // player1 busts
    dealerRanks.push_back(10);
    dealerRanks.push_back(8); // dealer 18, with T Up 
    MakeHandForPlayerIdxHandIdx(sim, ranks0, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks1, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    FrontloadShoe(sim, shoeRanks);
    sim->CheckInsuranceAndBlackjack();
    sim->PlayHand(0, 0);
    sim->PlayHand(1, 0);
    sim->PlayDealerHand();
    sim->PayoutWinners();
    testPassed &=  25 == sim->GetPlayerAt(0)->GetChips();
    testPassed &= -25 == sim->GetPlayerAt(1)->GetChips();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // Both players take one secondary soft total hit action
    // Player 0 wins
    // Player 1 loses
    //
    ResetTestEnv(sim);
    ref = "PlayHandHitTest " + std::to_string(refCount++);
    preTest = testPassed;
    ranks0.clear();
    ranks1.clear();
    dealerRanks.clear();
    shoeRanks.clear();
    ranks0.push_back(1);
    ranks0.push_back(1);
    ranks0.push_back(3); // player0 three card s15
    ranks1.push_back(3);
    ranks1.push_back(1);
    ranks1.push_back(2); // player1 three card s16
    shoeRanks.push_back(2); // player0 gets s17, hits again
    shoeRanks.push_back(4); // player0 gets 21
    shoeRanks.push_back(1); // player1 gets s17, hits again
    shoeRanks.push_back(2); // player1 gets s19
    dealerRanks.push_back(6);
    dealerRanks.push_back(10); // dealer 16, with 6 Up 
    shoeRanks.push_back(4); // dealer gets 20
    MakeHandForPlayerIdxHandIdx(sim, ranks0, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks1, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    FrontloadShoe(sim, shoeRanks);
    sim->CheckInsuranceAndBlackjack();
    sim->PlayHand(0, 0);
    sim->PlayHand(1, 0);
    sim->PlayDealerHand();
    sim->PayoutWinners();
    testPassed &=  25 == sim->GetPlayerAt(0)->GetChips();
    testPassed &= -25 == sim->GetPlayerAt(1)->GetChips();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // Player 0 wins
    // Player 1 busts
    // Dealer busts
    //
    ResetTestEnv(sim);
    ref = "PlayHandHitTest " + std::to_string(refCount++);
    preTest = testPassed;
    ranks0.clear();
    ranks1.clear();
    dealerRanks.clear();
    shoeRanks.clear();
    ranks0.push_back(10);
    ranks0.push_back(4);
    ranks1.push_back(2);
    ranks1.push_back(2);
    shoeRanks.push_back(5); // player0 gets 19
    shoeRanks.push_back(10); // player1 gets 14, hits again
    shoeRanks.push_back(10); // player1 busts
    dealerRanks.push_back(10);
    dealerRanks.push_back(6); // dealer 16, with T Up 
    shoeRanks.push_back(10); // dealer busts
    MakeHandForPlayerIdxHandIdx(sim, ranks0, 0, 0);
    MakeHandForPlayerIdxHandIdx(sim, ranks1, 1, 0);
    MakeHandForDealer(sim, dealerRanks);
    sim->GetPlayerAt(0)->SetInitialBet(sim->GetGame().get());
    sim->GetPlayerAt(1)->SetInitialBet(sim->GetGame().get());
    FrontloadShoe(sim, shoeRanks);
    sim->CheckInsuranceAndBlackjack();
    sim->PlayHand(0, 0);
    sim->PlayHand(1, 0);
    sim->PlayDealerHand();
    sim->PayoutWinners();
    testPassed &=  25 == sim->GetPlayerAt(0)->GetChips();
    testPassed &= -25 == sim->GetPlayerAt(1)->GetChips();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    return testPassed;
}

//******************************************************************************
//
// Player Stands Tests:
//
// When a player Stands, TODO
//
// TODO
//
//******************************************************************************

/**
 * This tests the Stand action of Sim::PlayHand()
 */
bool PlayHandStandTest(std::unique_ptr<Sim>& sim, bool verbose)
{
    bool testPassed = true;

    return testPassed;
}

//******************************************************************************
//
// Player Surrenders Tests:
//
// When a player Surrenders, TODO
//
// TODO
//
//******************************************************************************

/**
 * This tests the Surrender action of Sim::PlayHand()
 */
bool PlayHandSurrenderTest(std::unique_ptr<Sim>& sim, bool verbose)
{
    bool testPassed = true;

    return testPassed;
}
