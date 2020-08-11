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


int* parralelizeAnswer(int end, int *lookupTable) {
	int *answers = new int[end];
	int numProccesors = thread::hardware_concurrency();
	int *jobAllocation = splitUpJob(end, numProccesors);
	thread *allThreads = new thread[numProccesors];
	int lastEnd = 0;
	for (int i = 0; i < numProccesors; ++i) {
		allThreads[i] = thread(partialAnswer, answers, lastEnd, jobAllocation[i], lookupTable);
		lastEnd = jobAllocation[i] + 1;
	}
	for (int i = 0; i < numProccesors; ++i) {
		allThreads[i].join();
	}
	delete[] jobAllocation;
	delete[] allThreads;
	return answers;
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

/*
 * Splits up the programmatic task into approximately equal units of work.
 * Returns two dimensional array with start and end number for every processor
*/
int* splitUpJob(int upperBound, int numProcessors) {
	int *jobs = new int[numProcessors];
	int totalWork = getTotalWork(upperBound);
	int eachSlice = totalWork / numProcessors;
	int currentSlice = eachSlice;
	int currentEnd = 1;
	int currentPower = 0;
	int nextWork = 1;
	for (int i = 0; i < numProcessors; ++i) {
		while (currentSlice - nextWork > 0) {
			++currentEnd;
			if ((int) (log(currentEnd)/log(numProcessors)) != currentPower) {
				++currentPower;
				nextWork = (int) pow(numProcessors, currentPower);
			}
			currentSlice -= nextWork;
		}
		jobs[i] = currentEnd;
		++currentEnd;
	}
	jobs[numProcessors - 1] = upperBound;
	return jobs;
}



/*
 * Every power of 2 is 4 times as hard as the previous power of 2, since it is twice as long, and also twice as hard per number
 * Get total work to be done
 */
int getTotalWork(int upperBound) {
	int twoPower = (int) log2(upperBound - 1);
	int remainder = upperBound - pow(2, twoPower);
	return (pow(4, twoPower) - 1) / 3 + pow(2, twoPower + 1) * remainder; // first part is sum of finite geometric series
}


