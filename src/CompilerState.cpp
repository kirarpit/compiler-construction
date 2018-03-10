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
	Logger::log("Error Recovery Started");
	while (lexer.peek().value != TokenTable::TS[TN_semi]
			&& lexer.peek().value != TokenTable::TS[TN_clsbrc]
			&& lexer.peek().type != TT_EOF) {
		lexer.read();
	}

	if (lexer.peek().value != TokenTable::TS[TN_semi]) {
		reportError();
	}

	if (lexer.peek().value != TokenTable::TS[TN_clsbrc])
		lexer.read();
	error = false;
}
