#include"CompilerState.h"

int CompilerState::reportError() {

	Logger::log("Error Reported, total error count: \n");
	if (!muteCount) {
		error = true;
		return ++errorCount;
	}
	return errorCount;
}

void CompilerState::muteErrors() {
	++muteCount;
}

void CompilerState::unmuteErrors() {
	--muteCount;
}

int CompilerState::getErrorCount() {
	return errorCount;
}
