#ifndef INSURANCE_TEST_H
#define INSURANCE_TEST_H

/**
 * Helper functions
 */
void MakeHandForPlayerIdxHandIdx(std::unique_ptr<Sim>& sim, std::vector<int> ranks, int pIdx, int hIdx);
void MakeHandForDealer(std::unique_ptr<Sim>& sim, std::vector<int> ranks);

/**
 * This tests Sim::GetOptimalValue()
 */
bool InsuranceTest(std::unique_ptr<Sim>& sim, bool verbose = false);

#endif
