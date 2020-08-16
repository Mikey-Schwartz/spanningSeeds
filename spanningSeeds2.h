#ifndef SPANNINGSEED2S_H
#define SPANNINGSEED2S_H
int * generateEvenOdd(int upperBound);
int * findRangeSeeds(int lowerBound, int upperBound, const int *precomputedEvenOdd);
int findNumSeeds(int tap, const int *precomputedEvenOdd);
#endif
