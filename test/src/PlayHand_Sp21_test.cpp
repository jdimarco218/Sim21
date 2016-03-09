#include <assert.h>
#include <iostream>
#include <list>
#include <memory>
#include <vector>
#include "Sim.h"
#include "Card.h"
#include "Deck.h"
#include "Shoe.h"

#include "PlayHand_Sp21_test.h"
#include "TestUtil.h"

#define DEBUG true

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
bool PlayHandSp21Test(std::unique_ptr<Sim>& sim, bool verbose)
{
    bool testPassed = true;

    testPassed &= PlayHandSplitSp21Test(sim, verbose);
    testPassed &= PlayHandDoubleSp21Test(sim, verbose);
    //testPassed &= PlayHandHitSp21Test(sim, verbose);
    testPassed &= PlayHandStandSp21Test(sim, verbose);
    //testPassed &= PlayHandSurrenderSp21Test(sim, verbose);

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
bool PlayHandSplitSp21Test(std::unique_ptr<Sim>& sim, bool verbose)
{
    bool testPassed = true;
    bool preTest = true;

    std::vector<std::pair<int, int> > ranks0;
    std::vector<std::pair<int, int> > ranks1;
    std::vector<std::pair<int, int> > shoeRanks;
    std::vector<std::pair<int, int> > dealerRanks;
    std::string ref = "";
    int refCount = 0;

    // TEST CASE
    // SPLIT_X_SUPER
    // Player 0 splits
    // Player 1 goes for super!
    //
    ResetTestEnv(sim);
    ref = "PlayHandSplitSp21Test " + std::to_string(refCount++);
    preTest = testPassed;
    ranks0.clear();
    ranks1.clear();
    dealerRanks.clear();
    shoeRanks.clear();
    ranks0.push_back(std::make_pair(7, 3));
    ranks0.push_back(std::make_pair(7, 2)); // player0 has no super opportunity
    ranks1.push_back(std::make_pair(7, 1));
    ranks1.push_back(std::make_pair(7, 1)); // player1 has suited sevens!
    shoeRanks.push_back(std::make_pair(11, 2)); // player0 gets 17 on first hand
    shoeRanks.push_back(std::make_pair(12, 2)); // player0 gets 17 on second hand
    shoeRanks.push_back(std::make_pair(7, 1)); // player1 gets suited 21! WOW!
    dealerRanks.push_back(std::make_pair(7, 1)); // dealer 7 up, matches player1's
    dealerRanks.push_back(std::make_pair(11, 1)); // dealer 17, with 7 Up
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
    testPassed &=     0 == sim->GetPlayerAt(0)->GetChips();
    testPassed &=  4975 == sim->GetPlayerAt(1)->GetChips();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

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
bool PlayHandDoubleSp21Test(std::unique_ptr<Sim>& sim, bool verbose)
{
    bool testPassed = true;
    bool preTest = true;
    int  prevDaS = sim->GetGame()->GetDaS();
    int  prevS17 = sim->GetGame()->GetS17();
    int  prevNumDoubles = sim->GetGame()->GetNumDoubles();

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
    ref = "PlayHandDoubleSp21Test " + std::to_string(refCount++);
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
    shoeRanks.push_back(6); // player1 gets 17 on first hand
    shoeRanks.push_back(2); // should not be dealt
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
    // Both players redouble
    // Player 0 wins
    // Player 1 loses
    //
    ResetTestEnv(sim);
    // Set h17 rules with one redouble
    sim->GetGame()->SetNumDoubles(2);
    sim->GetGame()->SetS17(false);
    ref = "PlayHandDoubleSp21Test " + std::to_string(refCount++);
    preTest = testPassed;
    ranks0.clear();
    ranks1.clear();
    dealerRanks.clear();
    shoeRanks.clear();
    ranks0.push_back(3);
    ranks0.push_back(2); // player0 5
    ranks1.push_back(2);
    ranks1.push_back(3); // player1 5
    shoeRanks.push_back(6); // player0 gets 11, should redouble
    shoeRanks.push_back(12); // player0 gets 10, should win
    shoeRanks.push_back(6); // player1 gets 11, should redouble
    shoeRanks.push_back(4); // player1 gets 18, should stand and lose
    dealerRanks.push_back(6);
    dealerRanks.push_back(1); // dealer s17, with 6 Up 
    shoeRanks.push_back(2); // dealer should hit and get 19
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
    sim->GetGame()->SetNumDoubles(prevNumDoubles);
    sim->GetGame()->SetS17(prevS17);

    // TEST CASE
    // Both players double_x_5 then surrender
    //
    ResetTestEnv(sim);
    // Set h17 rules with one redouble
    sim->GetGame()->SetNumDoubles(2);
    sim->GetGame()->SetS17(false);
    ref = "PlayHandDoubleSp21Test " + std::to_string(refCount++);
    preTest = testPassed;
    ranks0.clear();
    ranks1.clear();
    dealerRanks.clear();
    shoeRanks.clear();
    ranks0.push_back(5);
    ranks0.push_back(5); // player0 10
    ranks1.push_back(6);
    ranks1.push_back(4); // player1 10
    shoeRanks.push_back(3); // player0 gets 13, should surrender
    shoeRanks.push_back(4); // player1 gets 14, should surrender
    dealerRanks.push_back(8);
    dealerRanks.push_back(9); // dealer 17, with 8 Up 
    shoeRanks.push_back(2); // player1 gets s19
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
    testPassed &= -25 == sim->GetPlayerAt(0)->GetChips();
    testPassed &= -25 == sim->GetPlayerAt(1)->GetChips();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}
    sim->GetGame()->SetNumDoubles(prevNumDoubles);
    sim->GetGame()->SetS17(prevS17);

    // TEST CASE
    // Both players double then stand
    // Player 0 wins
    // Player 1 loses
    //
    ResetTestEnv(sim);
    // Set h17 rules with one redouble
    sim->GetGame()->SetNumDoubles(2);
    sim->GetGame()->SetS17(false);
    ref = "PlayHandDoubleSp21Test " + std::to_string(refCount++);
    preTest = testPassed;
    ranks0.clear();
    ranks1.clear();
    dealerRanks.clear();
    shoeRanks.clear();
    ranks0.push_back(4);
    ranks0.push_back(6); // player0 10
    ranks1.push_back(5);
    ranks1.push_back(5); // player1 10
    shoeRanks.push_back(8); // player0 gets 18, should stand
    shoeRanks.push_back(6); // player1 gets 16, should stand
    dealerRanks.push_back(7);
    dealerRanks.push_back(11); // dealer 17, with 7 Up 
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
    sim->GetGame()->SetNumDoubles(prevNumDoubles);
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
bool PlayHandHitSp21Test(std::unique_ptr<Sim>& sim, bool verbose)
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
    ref = "PlayHandHitSp21Test " + std::to_string(refCount++);
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
    ref = "PlayHandHitSp21Test " + std::to_string(refCount++);
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
    ref = "PlayHandHitSp21Test " + std::to_string(refCount++);
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
    ref = "PlayHandHitSp21Test " + std::to_string(refCount++);
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
    ref = "PlayHandHitSp21Test " + std::to_string(refCount++);
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
bool PlayHandStandSp21Test(std::unique_ptr<Sim>& sim, bool verbose)
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
    // STAND_X_4
    // Player 0 takes action (stand)
    // Player 1 doesn't take action (hit), 5 card bonus win
    //
    ResetTestEnv(sim);
    ref = "PlayHandStandSp21Test " + std::to_string(refCount++);
    preTest = testPassed;
    ranks0.clear();
    ranks1.clear();
    dealerRanks.clear();
    shoeRanks.clear();
    ranks0.push_back(5);
    ranks0.push_back(1); // player0 s16
    ranks1.push_back(5);
    ranks1.push_back(1); // player1 s16
    shoeRanks.push_back(2); // player0 gets s18, stand_x_4
    shoeRanks.push_back(1); // player1 gets s17
    shoeRanks.push_back(1); // player1 gets s18, stand_x_4 -> hit
    shoeRanks.push_back(2); // player1 gets 20
    dealerRanks.push_back(2);
    dealerRanks.push_back(8); // dealer 10, with 2 Up
    shoeRanks.push_back(9); // dealer gets 19
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
    testPassed &= -25   == sim->GetPlayerAt(0)->GetChips();
    testPassed &=  37.5 == sim->GetPlayerAt(1)->GetChips();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // STAND_X_5
    // For this test, a hit if suited 6-7-8 is possible should be the primary
    // decision and STAND_X_5 should be the followup decision
    //
    // Player 0 takes action (stand)
    // Player 1 doesn't take action (hit), 6 card bonus win
    //
    ResetTestEnv(sim);
    ref = "PlayHandStandSp21Test " + std::to_string(refCount++);
    preTest = testPassed;
    ranks0.clear();
    ranks1.clear();
    dealerRanks.clear();
    shoeRanks.clear();
    ranks0.push_back(2);
    ranks0.push_back(3); // player0 5
    ranks1.push_back(3);
    ranks1.push_back(2); // player1 5
    shoeRanks.push_back(2); // player0 gets 7
    shoeRanks.push_back(7); // player0 gets 17, stand
    shoeRanks.push_back(2); // player1 gets 7
    shoeRanks.push_back(5); // player1 gets 12
    shoeRanks.push_back(2); // player1 gets 14, stand_x_5 -> hit
    shoeRanks.push_back(5); // player1 gets 19
    dealerRanks.push_back(5);
    dealerRanks.push_back(5); // dealer 10, with 5 Up
    shoeRanks.push_back(8); // dealer gets 18
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
    testPassed &= -25 == sim->GetPlayerAt(0)->GetChips();
    testPassed &=  50 == sim->GetPlayerAt(1)->GetChips();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

    // TEST CASE
    // STAND_X_6
    // Player 0 takes action (stand)
    // Player 1 doesn't take action (hit), 7 card bonus win
    //
    ResetTestEnv(sim);
    ref = "PlayHandStandSp21Test " + std::to_string(refCount++);
    preTest = testPassed;
    ranks0.clear();
    ranks1.clear();
    dealerRanks.clear();
    shoeRanks.clear();
    ranks0.push_back(2);
    ranks0.push_back(3); // player0 5
    ranks1.push_back(2);
    ranks1.push_back(3); // player1 5
    shoeRanks.push_back(2); // player0 gets 7, hit
    shoeRanks.push_back(9); // player0 gets 16, stand_x_6
    shoeRanks.push_back(2); // player1 gets 7
    shoeRanks.push_back(2); // player1 gets 9
    shoeRanks.push_back(3); // player1 gets 12
    shoeRanks.push_back(4); // player1 gets 16, stand_x_6 -> hit
    shoeRanks.push_back(4); // player1 gets 20
    dealerRanks.push_back(2);
    dealerRanks.push_back(8); // dealer 10, with 2 Up
    shoeRanks.push_back(9); // dealer gets 19
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
    testPassed &= -25 == sim->GetPlayerAt(0)->GetChips();
    testPassed &=  75 == sim->GetPlayerAt(1)->GetChips();
    if (!testPassed && preTest) {std::cout << ref << " failed." << std::endl;}

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
bool PlayHandSurrenderSp21Test(std::unique_ptr<Sim>& sim, bool verbose)
{
    bool testPassed = true;

    return testPassed;
}
