//============================================================================
// Name        : spanningSeeds2.cpp
// Author      : Avraham Kahan
// Version     : 2
// Copyright   : MIT License
//============================================================================

//#include "spanningSeeds2.h"
#include "threading.h"
#include <iostream>
#include <cmath>
using std::cout; using std::endl; using std::cin; using std::log2; using std::pow;

//function declarations
int * findRangeSeeds(int lowerBound, int upperBound, const int *precomputedEvenOdd);
int findNumSeeds(int tap, const int *precomputedEvenOdd);
int getNewState(int currentState, int power2, int tap, const int *precomputedEvenOdd);
int * generateEvenOdd(int upperBound);
int * findRangeSeeds(int lowerBound, int upperBound);

/* recursively find if binary represetation of all integers n for 0 <= n <= upperBound contains even or odd number of ones
 for every integer in the array, an entry of 1 means odd number of 1s. An entry of 0 means even number of ones */
int * generateEvenOdd(int upperBound) {
	int *evenOdd = new int[upperBound + 1];
	evenOdd[0] = 0;
	evenOdd[1] = 1;
	for (int i = 2; i <= upperBound; ++i) {

		evenOdd[i] = (evenOdd[i - (int) pow(2, (int)(log2(i)))] + 1) % 2;
	}
	return evenOdd;
}

/*
 * Return index of target in given array, othwerwise return -1
 */
int getIndex(const int *array, int length, int target) {
	for (int i = 0; i < length; i++) {
		if (array[i] == target) {
			return i;
		}
	}
	return -1;
}

int * findRangeSeeds(int lowerBound, int upperBound, const int *precomputedEvenOdd) {
	int *output = new int[upperBound - lowerBound + 1];  //change
	if (lowerBound == 0) {
		++lowerBound;
	}
	//const int *precomputedEvenOdd = generateEvenOdd(upperBound);
	for (int n = lowerBound; n <= upperBound - lowerBound + 1; ++n) {
		output[n - lowerBound] = findNumSeeds(n, precomputedEvenOdd);
	}
	return output;
}

int findNumSeeds(int tap, const int *precomputedEvenOdd) {
	int tapLength = (int) (log2(tap)) + 1;
	int pastStates[(int) pow(2, tapLength)]{0};
	int reqSeeds = 1;
	pastStates[0] = 1;
	int changedStates = 1;
	int currentState = 1;
	while (changedStates < (int) pow(2, tapLength)){
		++reqSeeds;
		currentState = getIndex(pastStates, sizeof(pastStates)/sizeof(*pastStates), 0);
		while(pastStates[currentState] == 0) {
			changedStates +=1;
			pastStates[currentState] = 1;
			currentState = getNewState(currentState, tapLength - 1, tap, precomputedEvenOdd);
		}
	}
	return reqSeeds;
}

int getNewState(int currentState, int power2, int tap, const int *precomputedEvenOdd) {
	int firstBit = precomputedEvenOdd[tap & currentState];
	if (currentState >= (int) pow(2, power2)) {
		currentState -= (int) (pow(2, power2));
	}
	return currentState * 2 + firstBit;
}
/*
int * useCli() {
	int lowerBound, upperBound;
	cout << "Input lower bound \n >>>" << endl;
	cin >> lowerBound;
	cout << "Input upper bound \n >>> " << endl;
	cin >> upperBound;
	return findRangeSeeds(lowerBound, upperBound);
}*/

int main() {
	cout << getTotalWork(9) << " is total work" << endl;
	int *z = splitUpJob(9, 4);
	for (int i = 0; i < 4; ++i) {
		cout << z[i] << endl;
	}

	/*
	int l = 0;
	int h = 1024;
	const int precomputedEvenOdd = generateEvenOdd(upperBound);
	int * rs = findRangeSeeds(l, h);
	for (int i = 0; i < h; i++) {
		cout << "tap " << i + 1 << " requires " << rs[i] << " restarts " << endl;
	}

	return 0;*/
}

