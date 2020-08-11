#ifndef THREADING_H
#define THREADING_H

int* parralelizeAnswer(int end, int *lookupTable);
int* splitUpJob(int upperBound, int numProcessors);
int getTotalWork(int upperBound);

#endif
