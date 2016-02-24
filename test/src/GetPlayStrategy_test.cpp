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

    // TEST CASE
    // SP21 H17
    //
    sim->GetGame()->SetS17(false);
    testPassed &= sim->GetPlayerAt(0)->GetPlayStrategy(sim->GetGame()) ==
                  sim->GetPlayerAt(0)->bs_sp_h17;

    return testPassed;
}

