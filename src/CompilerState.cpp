#include"CompilerState.h"

int CompilerState::reportError() {

	Logger::log("Error Reported, total error count: \n");
	error = true;
	return ++errorCount;
}

int CompilerState::getErrorCount() {
	return errorCount;
}
