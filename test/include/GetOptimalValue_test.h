#ifndef GETOPTIMALVALUE_TEST_H
#define GETOPTIMALVALUE_TEST_H

/**
 * Helper function to create a hand
 */
void MakeHand(std::vector<std::unique_ptr<Card> >& hand, std::vector<int> ranks);

/**
 * This tests Sim::GetOptimalValue()
 */
bool GetOptimalValueTest(std::unique_ptr<Sim>& sim);

#endif
