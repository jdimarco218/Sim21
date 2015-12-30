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
// Maximum splits, follow-up action
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

    std::vector<int> ranks0;
    std::vector<int> ranks1;
    std::vector<int> shoeRanks;
    std::vector<int> dealerRanks;
    std::string ref = "";
    int refCount = 0;

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
    if(verbose){std::cout << "test. chips p0: " << sim->GetPlayerAt(0)->GetChips() << std::endl;}
    if(verbose){std::cout << "test. chips p1: " << sim->GetPlayerAt(1)->GetChips() << std::endl;}
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
    if(1){std::cout << "test. chips p0: " << sim->GetPlayerAt(0)->GetChips() << std::endl;}
    if(1){std::cout << "test. chips p1: " << sim->GetPlayerAt(1)->GetChips() << std::endl;}
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
    if(1){std::cout << "test. chips p0: " << sim->GetPlayerAt(0)->GetChips() << std::endl;}
    if(1){std::cout << "test. chips p1: " << sim->GetPlayerAt(1)->GetChips() << std::endl;}
    testPassed &=  100 == sim->GetPlayerAt(0)->GetChips();
    testPassed &= -100 == sim->GetPlayerAt(1)->GetChips();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    return testPassed;
}

//******************************************************************************
//
// Player Doubles Tests:
//
// When a player Doubles, TODO
//
// TODO
//
//******************************************************************************

/**
 * This tests the Double action of Sim::PlayHand()
 */
bool PlayHandDoubleTest(std::unique_ptr<Sim>& sim, bool verbose)
{
    bool testPassed = true;

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
    if(verbose){std::cout << "test. chips p0: " << sim->GetPlayerAt(0)->GetChips() << std::endl;}
    if(verbose){std::cout << "test. chips p1: " << sim->GetPlayerAt(1)->GetChips() << std::endl;}
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
    if(verbose){std::cout << "test. chips p0: " << sim->GetPlayerAt(0)->GetChips() << std::endl;}
    if(verbose){std::cout << "test. chips p1: " << sim->GetPlayerAt(1)->GetChips() << std::endl;}
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
    if(verbose){std::cout << "test. chips p0: " << sim->GetPlayerAt(0)->GetChips() << std::endl;}
    if(verbose){std::cout << "test. chips p1: " << sim->GetPlayerAt(1)->GetChips() << std::endl;}
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
    if(verbose){std::cout << "test. chips p0: " << sim->GetPlayerAt(0)->GetChips() << std::endl;}
    if(verbose){std::cout << "test. chips p1: " << sim->GetPlayerAt(1)->GetChips() << std::endl;}
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
