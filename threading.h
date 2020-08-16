#ifndef THREADING_H
#define THREADING_H

int* parralelizeAnswer(int start, int end, int *lookupTable);
int* splitUpJob(int upperBound, int numProcessors);
int getTotalWork(int upperBound);
int * splitUpJob(int lowerBound, int upperBound, int numProccesors);

#endif
