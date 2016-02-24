#ifndef PLAYHAND_SP21_TEST_H
#define PLAYHAND_SP21_TEST_H

/**
 * This tests each of the actions of Sim::PlayHand()
 */
bool PlayHandSp21Test(std::unique_ptr<Sim>& sim, bool verbose = false);

/**
 * This tests the Split action of Sim::PlayHand()
 */
bool PlayHandSplitSp21Test(std::unique_ptr<Sim>& sim, bool verbose = false);

/**
 * This tests the Double action of Sim::PlayHand()
 */
bool PlayHandDoubleSp21Test(std::unique_ptr<Sim>& sim, bool verbose = false);

/**
 * This tests the Hit action of Sim::PlayHand()
 */
bool PlayHandHitSp21Test(std::unique_ptr<Sim>& sim, bool verbose = false);

/**
 * This tests the Stand action of Sim::PlayHand()
 */
bool PlayHandStandSp21Test(std::unique_ptr<Sim>& sim, bool verbose = false);

/**
 * This tests the Surrender action of Sim::PlayHand()
 */
bool PlayHandSurrenderSp21Test(std::unique_ptr<Sim>& sim, bool verbose = false);

#endif
