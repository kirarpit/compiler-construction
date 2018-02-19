#include"CompilerState.h"

int CompilerState::reportError() {

	Logger::log(
			"Error Reported, total error count: " + to_string(errorCount + 1)
					+ "\n");
	if (!muter) {
		error = true;
		return ++errorCount;
	}
	return 0;
}

void CompilerState::muteErrors() {
	++muter;
}

void CompilerState::unmuteErrors() {
	--muter;
}
