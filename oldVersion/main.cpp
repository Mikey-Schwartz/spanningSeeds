/*
 * main.cpp
 *
 *  Created on: Jul 16, 2020
 *      Author: avraham
 */
#include <iostream>
#include <array>
#include <cmath>
#include <vector>
#include <list>
#include <iterator>

using namespace std;


int * convertToBase(int num, int base) {
	int repSize = (log2(num)/log2(base)) + 1;
 	int * representation = new int[repSize];
	int mod = 0;
	for (int i = 0; i < repSize ; i++) {
		mod = num % base;
		representation[i] = mod;
		num = (num / base);
		}
	return representation;
	}



int getIndex(const int *array, int length, int target) {
	for (int i = 0; i < length; i++) {
		if (array[i] == target) {
			return i;
		}
	}
	throw logic_error("Should be at least one 0 in the array");
}


// num is not copied since it is modified in due course of the function
list<int> convertToBaseList(int num, int base){
	list<int> representation;
	while (num > 0) {
	        representation.push_back(num % base);
       		num = (num/base);
	}
	return representation;
}

/*void fillOut(list<int> &b2rep, const int &numSlots) {
	if (numSlots > b2rep.size()) {
		for (int i = 0; i < numSlots - b2rep.size(); i++) {
			numSlots.push_back(0);
		}
	}
}*/


int dotProduct(int *taps, list<int> &B2Rep){
	int product = 0;
	int i = 0;
	list<int>::iterator it;
	for (auto it = B2Rep.begin(); it != B2Rep.end(); it++){
		product += *it * taps[i] ;
		i++;
	}
	return product;
}


// maxLength is maximum acceptable length of the list
void updateB2(list<int> &b2rep, int newNum, unsigned int maxLength) {
	b2rep.push_front(newNum);
	//cout << b2rep.size() << "is size" << endl;
	if (b2rep.size() == maxLength + 1) {
		b2rep.pop_back();
	}
}


int toBase10(list<int> &b2) {
	int base10Value = 0;
	int slot = 0;
	list<int>::iterator it;
	for (auto it = b2.begin(); it != b2.end(); ++it) {
		base10Value += *it * pow(2, slot);
		slot+=1;
	}
	return base10Value;
}

int findNumSeeds(int num, int base) {
	int reqSeeds = 1;
	int *taps = convertToBase(num, base);
	unsigned int tapsLength = (log2(num)/log2(base)) + 1;
	int pastStates[(int) pow(base, tapsLength) ]{0};
	pastStates[0] = 1;
	int changedStates = 1;
	int currentState = 1;
	while (changedStates < (int) pow(2, tapsLength)){
		reqSeeds++;  // 2
		currentState = getIndex(pastStates, sizeof(pastStates)/sizeof(*pastStates) ,0);
		list<int> currentStateB2 = convertToBaseList(currentState, base);
		while(pastStates[currentState] == 0) {
			changedStates +=1;
			pastStates[currentState] = 1;
			updateB2(currentStateB2, dotProduct(taps, currentStateB2)%2, tapsLength);
			currentState = toBase10(currentStateB2);
		}
	}
	delete[] taps;
	taps = NULL;
	//cout << "req seeds " << reqSeeds << "for " << num << endl;
	return reqSeeds;
}


int * findRangeSeeds(int lowerBound, int upperBound, int base) {
	// assert lower > 0
	int *output = new int[upperBound - lowerBound + 1];  //change
	if (lowerBound == 0) {
		output[0] = 1;
		lowerBound++;
	}
	for (int n = lowerBound; n <= upperBound; n++) {
		output[n] = findNumSeeds(n, base);
	}
	//cout << "completed" << endl;
	return output;
}


int * useCli() {
	int base, lowerBound, upperBound;
	cout << "Input Base \n >>>" << endl;
	cin >> base;
	cin >> base;
	cout << "Input lower bound \n >>>" << endl;
	cin >> lowerBound;
	cout << "Input upper bound \n >>> ";
	cin >> upperBound;
	return findRangeSeeds(base, lowerBound, upperBound);
}


int main() {


	int l = 0;
	int h = 10000;
	int * rs = findRangeSeeds(l, h, 2);
	/*for (int i = 0; i < 1025; i++) {
		cout << rs[i] << "#: " << i << endl;
	}*/
	delete[] rs;
//	cout << "success" << endl;
	return 0;
}

