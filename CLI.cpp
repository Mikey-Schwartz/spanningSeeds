#include <iostream>
#include <unordered_map>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <time.h>
#include "spanningSeeds2.h"
#include "threading.h"
#include "errorMessages.h"


using std::cout; using std::endl; using std::unordered_map; using std::to_string;
using std::string; using std::stringstream; using std::ofstream;

// function declarations
void populateArguments(int argc, char *argv[], unordered_map<char, int> &arguments);
void tokenizeInput(int argc, char *argv[], unordered_map<char, int> &arguments);
void loadIntParameter(char field, char *number, unordered_map<char, int> &arguments);
void checkForInvalidInputs(unordered_map<char, int> &arguments);
void runProgram(unordered_map<char, int> &arguments);
void outputSingleAnswer(unordered_map<char, int> &arguments, int answer);
void outputRangeAnswers(unordered_map<char, int> &arguments, int *answer);

void populateArguments(int argc, char *argv[], unordered_map<char, int> &arguments) {
	if (argc == 1) {
		cout << getEmptyMessage() << endl;
		exit(-1);
	}
	else {
		tokenizeInput(argc, argv, arguments);
	}
	checkForInvalidInputs(arguments);
}


void tokenizeInput(int argc, char *argv[], unordered_map<char, int> &arguments) {
	char help[] = "--help";
	if (strcmp(argv[1], help) == 0) {
		helpMessage(); // exits
	}
	bool lastWasIntegerArg = false;
	char lastParam;
	char field;
	unordered_map<char, int>::const_iterator parameter;
	for (int i = 1; i < argc; i++) {
		field = argv[i][1];
		if (argv[i][0] != '-' && !lastWasIntegerArg) {
			syntaxError(); // invalid syntax
		}
		else if (lastWasIntegerArg) {
			loadIntParameter(lastParam, argv[i], arguments);
			lastWasIntegerArg = false;
		}
		else if (field == 'h' || field == 'n' ||field == 'l') {  // may cause problems with char array
			lastWasIntegerArg = true;
			lastParam = field;
		}
		else {
			parameter = arguments.find(field);
			if (parameter == arguments.end()) {
				invalidArgumentError(field);
			}
			else {
				arguments[field] = 1;
			}
		}
	}
}

void loadIntParameter(char field, char *number, unordered_map<char, int> &arguments) {
	stringstream convertToInt{number};
	int integerValue = -1;
	if (!(convertToInt >> integerValue)) {
		nonIntegerParam();
	}
	else {
		if (field == 'l') {
			arguments['l'] = integerValue;
		}
		else {
			arguments.insert({field, integerValue});
		}
	}
}



void checkForInvalidInputs(unordered_map<char, int> &arguments) {
	unordered_map<char, int>::const_iterator parameter1;
	unordered_map<char, int>::const_iterator parameter2;
	bool nExists = arguments.find('n') != arguments.end();
	bool hExists = arguments.find('h') != arguments.end();
	bool lExists = arguments['l'] != 0;
	if (nExists && (hExists || lExists)) {
		invalidIntegerCombinationError(); // exit
	}
	else if (!nExists && !hExists) {
		noUpperBoundError();
	}
	else if(arguments['l'] < 0) {
		negativeBoundError();
	}
	else if ((nExists && arguments['n'] < 0) || (hExists && arguments['h'] < 0)) {
		negativeBoundError();
	}
	else if (hExists && arguments['l'] >= arguments['h']) {
		upperLowerError();
	}
}



void runProgram(unordered_map<char, int> &arguments) {
	int *lookupTable;
	if (arguments.find('n') != arguments.end()) {
		int *lookupTable = generateEvenOdd(arguments['n']);
		int answer = findNumSeeds(arguments['n'], lookupTable);
		outputSingleAnswer(arguments, answer);
	}
	else if (arguments['p'] == 1 && (arguments['h'] - arguments['l'] > 50)) {
		arguments['h']+=1;
		lookupTable = generateEvenOdd(arguments['h']);
		int *parralelAnswer = parralelizeAnswer(arguments['l'], arguments['h'], lookupTable);
		arguments['h']-=1;
		outputRangeAnswers(arguments, parralelAnswer);
	}
	else {
		lookupTable = generateEvenOdd(arguments['h']);
		int *rangeAnswer = findRangeSeeds(arguments['l'], arguments['h'], lookupTable);
		outputRangeAnswers(arguments, rangeAnswer);
	}
}

void outputSingleAnswer(unordered_map<char, int> &arguments, int answer) {
	if (arguments['f'] == 1) {
		ofstream answerFile;
		answerFile.open(to_string(arguments['n']) + "_answer.txt");
		answerFile << "SEED NUMBER" << endl;
		answerFile << arguments['n'] << " " << answer << endl;
		answerFile.close();
	}
	else {
		cout << "SEED NUMBER" << endl;
		cout << arguments['n'] << " " << answer << endl;
	}
}

void outputRangeAnswers(unordered_map<char, int> &arguments, int *answer) {
	if (arguments['f'] == 1) {
		ofstream answerFile;
		answerFile.open(to_string(arguments['l']) +  "-" + to_string(arguments['h']) + "answers.txt");
		answerFile << "SEED NUMBER" << endl;
		for (int i = 0; i <= arguments['h'] - arguments['l']; ++i) {
			answerFile << arguments['l'] + i << " " << answer[i] << '\n';
		}
		answerFile.close();
	}
	else {
		for (int i = 0; i <= arguments['h'] - arguments['l']; ++i) {
			cout << arguments['l'] + i << " " << answer[i] << "\n" << endl;
		}
	}
}


int main(int argc, char *argv[]) {

	unordered_map<char, int> arguments = {
			{'p', 0}, // parallel
			{'l', 0}, // lower bound. Default = 1
			{'f', 0}, // writes to newline separated file
	};
	populateArguments(argc, argv, arguments);
	runProgram(arguments);

}
