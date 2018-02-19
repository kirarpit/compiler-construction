#include"CompilerState.h"

int CompilerState::reportError() {
	Logger::log("Error Reported, total error count: \n");

	if (errorCount == 9) {
		exit(10);
	}
	error = true;
	return ++errorCount;
}

int CompilerState::getErrorCount() {
	return errorCount;
}
