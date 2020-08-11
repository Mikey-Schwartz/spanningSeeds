#include <iostream>
#include <unordered_map>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <time.h>
#include "spanningSeeds2.h"
#include "threading.h"



using std::vector; using std::unordered_map; using std::string; using std::stringstream; using std::ofstream;

void runProgram(unordered_map<char, int> &arguments) {
	int *lookupTable = generateEvenOdd()
	if (arguments.find("n") != arguments.end()) {
		int answer = findNumSeeds(arguments[n], lookupTable);
		outputAnswer(arguments, answer);
	}

	int *lookupTable = generateEvenOdd()
	if (arguments["p"] == 1) {

	}
}

void outputAnswer(unordered_map<char, int> &arguments, int answer) {
	if (arguments["f"] == 1) {
		ofstream answerFile;
		time_t currentTime = time(NULL);
		answerfile.open(ctime(&currentTime) + "answers.txt");
		outfile << "Format SEED NUMBER" << endl;
		outfile << arguments["n"] << " " << answer << endl;
		outfile.close();
	}
	else {
		cout << "Format SEED NUMBER" << endl;
		cout << arguments["n"] << " " << answer << endl;
	}
}

void outputAnswers(nordered_map<char, int> &arguments, int* answer) {
	if (arguments["f"] == 1) {
		ofstream answerFile;
		time_t currentTime = time(NULL);
		answerfile.open(ctime(&currentTime) + "answers.txt");
		outfile << "Format SEED NUMBER" << endl;
		outfile << arguments["n"] << " " << answer << endl;
		outfile.close();
	}
}

void populateArguments(int argc, char *argv[], unordered_map<char, int> arguments) {
	if (argc == 1) {
		cout << getEmptyMessage() << endl;
		exit(-1);
	}
	else {
		tokenizeInput(argc, argv, arguments);
	}
	checkForInvalidInputs(arguments);
	runProgram(arguments);
}

void checkForInvalidInputs(unordered_map<char, int> &arguments) {
	unordered_map<char, int>::const_iterator parameter1;
	unordered_map<char, int>::const_iterator parameter2;
	if (arguments.find("n") != arguments.end() && (arguments.find("h") != arguments.end()) {
		invalidIntegerCombinationError(); // exit
	}
	else if (arguments.find("h") == arguments.end()) {
		noUpperBoundError();
	}
	else if(arguments["l"] < 0) {
		negativeLowerBoundError();
	}
	else if (arguments["l"] >= arguments["h"]) {
		upperLowerError();
	}
}

void negativeLowerBoundError() {
	cout << "Negative lower bound provided" << endl;
	offerHelp();
	exit();
}

void noUpperBoundError() {
	cout << "No upper bound or specific seed provided. One of the two must be provided" << endl;
	offerHelp();
	exit();
}

void upperLowerError() {
	cout << "provided lower bound greater or equal to provided upper bound" << endl;
	offerHelp();
	exit()
}

void invalidIntegerCombinationError() {
	cout << "Invalid combination of integer options. Please remember that if the -n field is set, -h cannot also be set" << endl;
	offerHelp();
	exit();
}

void offerHelp() {
	cout << "type 'registerSequences --help' for help" << endl;
}

void tokenizeInput(unordered_map<char, int> &arguments) {
	if (argv[2] == "--help") {
		helpMessage(); // exits
	}
	bool lastWasIntegerArg = false;
	char lastParam, field;
	unordered_map<char, int>::const_iterator parameter;
	for (int i = 1; i < argc, i++) {
		if (argv[i][0] != "-" && !lastWasIntegerArg) {
			syntaxError(); // invalid syntax
		}
		field = argv[i][1];
		else if (lastWasIntegerArg) {
			loadIntParameter(lastParam, argv[i], arguments);
			lastWasIntegerArg = false;
		}
		else if (field == "h" || field == "n" ||field == "l") {  // may cause problems with char array
			lastWasIntegerArg = true;
			lastParam = argv[i];
		}
		else {
			parameter = arguments.find(argv[i]);
			if (parameter == arguments.end()) {
				invalidArgumentError();
			}
			else {
				arguments[argv[i]] = 1;
			}
		}
	}
}

void invalidArgumentError() {
	cout << "Invalid Argument: '" << argv[i] << "' " << endl;
	offerHelp();
	exit();
}

void syntaxError() {
	cout << "Improper syntax" << endl;
	offerHelp();
	exit()
}

void loadIntParameter(char field, char *number, unordered_map<char, int> &arguments) {
	stringstream convertToInt{number};
	int integerValue = -1;
	if (!(convertToInt >> integerValue)) {
		cout << "Non integer value supplied to integer field" << endl;
		offerHelp();
		exit()
	}
	else {
		arguments[field] = integerValue;
	}
}

void helpMessage() {
	cout << "Invalid Input" << endl;
	cout << getEmptyMessage() << endl;
	exit();
}

string getEmptyMessage() {
	string errorMessage = "No range of seeds or single seed specified! Program Terminated \n "
			"Author Avraham Kahan and Mikey Schwartz (avrahamkahan123@gmail.com)\n"
			"Usage: $ registerSequences {-n | -h} [number] 
			"Optional Arguments "
			"-p for parralel computation. Default = false\n"
			"-f for file output. Default = false\n"
			"-l for command line. Default = true\n"
	return errorMesssage;
}
int main(int argc, char *argv[]) {
	unordered_map<char, int> arguments = {
			{"p", 0}, // parralel
			{"l", 1}, // lower bound. Default = 1
			{"f", 0}, // writes to file
	};
	populateArguments(argc, argv, arguments);
}
