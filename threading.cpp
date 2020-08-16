#include <cstdlib>
#include <cmath>
#include <pthread.h>
#include <thread>
#include "spanningSeeds2.h"

using std::thread;


int* splitUpJob(int upperBound, int numProcessors);
int getTotalWork(int upperBound);
void fillIn(int *answers, int *toBeFilled, int start, int length);
void partialAnswer(int *answers, int start, int end, int *lookupTable);
int * splitUpJob(int lowerBound, int upperBound, int numProcessors);


int* parralelizeAnswer(int start, int end, int *lookupTable) { // needs implementation for start
	int *answers = new int[end];
	int numProcessors = thread::hardware_concurrency();
	int *jobAllocation = start < 2 ? splitUpJob(end, numProcessors) : splitUpJob(start, end, numProcessors); // calculate it differently if start is 0
	thread *allThreads = new thread[numProcessors];
	int lastEnd = 0;
	for (int i = 0; i < numProcessors; ++i) {
		allThreads[i] = thread(partialAnswer, answers, lastEnd, jobAllocation[i], lookupTable);
		lastEnd = jobAllocation[i] + 1;
	}
	for (int i = 0; i < numProcessors; ++i) {
		allThreads[i].join();
	}
	delete[] jobAllocation;
	delete[] allThreads;
	return answers;
}

/*
 * Splits up the programmatic task into approximately equal units of work.
 * Returns two dimensional array with start and end number for every processor
*/
int * splitUpJob(int upperBound, int numProcessors) {
	int *jobs = new int[numProcessors];
	int totalWork = getTotalWork(upperBound);
	int eachSlice = totalWork / numProcessors;
	int currentSlice, currentEnd = 1;
	int currentPower = 0;
	int nextWork = 1;
	for (int i = 0; i < numProcessors; ++i) {
		currentSlice = eachSlice;
		while (currentSlice - nextWork > 0) {
			++currentEnd;
			currentSlice -= nextWork;
			if ((int) (log2(currentEnd) + 1) != currentPower) {
				++currentPower;
				nextWork = (int) pow(2, currentPower);
			}
		}
		jobs[i] = currentEnd;
		++currentEnd;
	}
	jobs[numProcessors - 1] = upperBound;
	return jobs;
}


//NOTE: fix for case where u - l > numProcessors
int * splitUpJob(int lowerBound, int upperBound, int numProcessors) {
	int *jobs = new int[numProcessors];
	int totalWork = getTotalWork(upperBound) - getTotalWork(lowerBound);
	int eachSlice = totalWork / numProcessors;
	int currentSlice, currentEnd = lowerBound;
	int currentPower = (int) log2(lowerBound);
	int nextWork = (int) pow(2, currentPower);
	for (int i = 0; i < numProcessors - 1; ++i) {  // last processors work assigned by default
			currentSlice = eachSlice;
			while (currentSlice - nextWork > 0) {
				++currentEnd;
				currentSlice -= nextWork;
				if ((int) log2(currentEnd) != currentPower) {
					++currentPower;
					nextWork = (int) pow(2, currentPower);
				}
			}
		jobs[i] = currentEnd;
		++currentEnd;
	}
	jobs[numProcessors - 1] = upperBound;
	// adjust
	return jobs;
}

/*
 * Every power of 2 is 4 times as hard as the previous power of 2, since it is twice as long, and also twice as hard per number
 * Get total work to be done
 */
int getTotalWork(int upperBound) {
	int twoPower = (int) log2(upperBound + 1);
	int remainder = upperBound - pow(2, twoPower) + 1;
	return (pow(4, twoPower) - 1) / 3 + pow(2, twoPower) * remainder; // first part is sum of finite geometric series
}


void partialAnswer(int *answers, int start, int end, int *lookupTable) {
	int *partialAnswer = findRangeSeeds(start, end, lookupTable);
	fillIn(partialAnswer, answers, start, end - start);
}


void fillIn(int *source, int *toBeFilled, int start, int length) {
	for (int i = 0; i < length; ++i) {
		toBeFilled[start + i] = source[i];
	}
}

