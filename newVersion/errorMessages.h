#ifndef ERRORMESSAGES_H
#define ERRORMESSAGES_H

#include <string>

std::string getEmptyMessage();
void offerHelp();
void helpMessage();
void syntaxError();
void invalidArgumentError(char argument);
void negativeBoundError();
void noUpperBoundError();
void upperLowerError();
void invalidIntegerCombinationError();
void nonIntegerParam();

#endif
