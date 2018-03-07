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
