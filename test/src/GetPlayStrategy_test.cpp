#include <assert.h>
#include <iostream>
#include <list>
#include <memory>
#include <vector>
#include "Sim.h"
#include "Card.h"
#include "Deck.h"
#include "Shoe.h"

#include "GetPlayStrategy_test.h"
#include "TestUtil.h"

#define DEBUG false

//******************************************************************************
//
// Tests:
//
// Test that each player strategy is selected for the correct games/rules
//
//******************************************************************************

bool GetPlayStrategySp21Test(std::unique_ptr<Sim>& sim, bool verbose)
{
    bool testPassed = true;

    auto& player = sim->GetPlayerAt(0);

    // TEST CASE
    // SP21 H17
    // redoubling allowed
    //
    sim->GetGame()->SetS17(false);
    sim->GetGame()->SetNumDoubles(1);
    testPassed &= player->GetPlayStrategy(sim->GetGame(), player->GetHand(0)) ==
                  player->bs_sp_nrd_h17;

    // TEST CASE
    // SP21 H17
    // redoubling allowed
    // get map after first double
    //
    sim->GetGame()->SetNumDoubles(2);
    player->IncrementDoubleAtIdx(0);
    testPassed &= player->GetPlayStrategy(sim->GetGame(), player->GetHand(0)) ==
                  player->bs_sp_rd_1d_h17;

    return testPassed;
}

