#include"CompilerState.h"

int CompilerState::reportError() {

	Logger::log(
			"Error Reported, total error count: " + to_string(errorCount + 1)
					+ "\n");
	error = true;
	return ++errorCount;
}
