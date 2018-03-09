#include"CompilerState.h"

void CompilerState::reportError() {
	error = true;
	++errorCount;

	Logger::log("Error Reported, total error count: %d", errorCount);

	if (errorCount == 10) {
		exit(10);
	}
}

int CompilerState::getErrorCount() {
	return errorCount;
}

void CompilerState::recover() {
	while (lexer.peek().value != ";" && lexer.peek().value != "}"
			&& lexer.peek().type != "EOF") {
		lexer.read();
	}

	if (lexer.peek().value != ";") {
		reportError();
	}

	lexer.read();
	error = false;
}
