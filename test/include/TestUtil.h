#ifndef TEST_UTIL_H
#define TEST_UTIL_H

void ResetTestEnv(std::unique_ptr<Sim>& sim);
void FrontloadShoe(std::unique_ptr<Sim>& sim, std::vector<int> ranks);
void MakeHandForPlayerIdxHandIdx(std::unique_ptr<Sim>& sim, std::vector<int> ranks, int pIdx, int hIdx);
void MakeHandForDealer(std::unique_ptr<Sim>& sim, std::vector<int> ranks);

#endif
