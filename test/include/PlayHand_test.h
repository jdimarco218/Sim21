#ifndef PLAYHAND_TEST_H
#define PLAYHAND_TEST_H

/**
 * This tests each of the actions of Sim::PlayHand()
 */
bool PlayHandTest(std::unique_ptr<Sim>& sim, bool verbose = false);

/**
 * This tests the Split action of Sim::PlayHand()
 */
bool PlayHandSplitTest(std::unique_ptr<Sim>& sim, bool verbose = false);

/**
 * This tests the Double action of Sim::PlayHand()
 */
bool PlayHandDoubleTest(std::unique_ptr<Sim>& sim, bool verbose = false);

/**
 * This tests the Hit action of Sim::PlayHand()
 */
bool PlayHandHitTest(std::unique_ptr<Sim>& sim, bool verbose = false);

/**
 * This tests the Stand action of Sim::PlayHand()
 */
bool PlayHandStandTest(std::unique_ptr<Sim>& sim, bool verbose = false);

/**
 * This tests the Surrender action of Sim::PlayHand()
 */
bool PlayHandSurrenderTest(std::unique_ptr<Sim>& sim, bool verbose = false);

#endif
