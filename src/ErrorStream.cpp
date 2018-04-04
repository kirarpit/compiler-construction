#include<ErrorStream.h>
#include<CompilerState.h>
#include<Logger.h>
#include<Lexer.h>
#include<SymbolTable.h>
#include<Node.h>
#include <Type.h>

void ErrorStream::reportParseError(CompilerState &cs) {
	reportError();
	es << "Error while parsing AST @ " << cs.lexer.peek().print() << "\n";
}

void ErrorStream::reportError() {
	Logger::log("Error Reported, total error count: %d", errorCount + 1);

	error = true;
	++errorCount;
	if (errorCount == 10) {
		exit(10);
	}
}

int ErrorStream::getErrorCount() {
	return errorCount;
}

void ErrorStream::recover(CompilerState &cs) {
	Logger::log("Error Recovery Started");

	while (cs.lexer.peek().value != TokenTable::TS[TN_semi]
			&& cs.lexer.peek().value != TokenTable::TS[TN_clsbrc]
			&& cs.lexer.peek().type != TT_EOF) {
		cs.lexer.read();
	}

	if (cs.lexer.peek().value != TokenTable::TS[TN_semi])
		reportParseError(cs);

	if (cs.lexer.peek().value != TokenTable::TS[TN_clsbrc])
		cs.lexer.read();

	error = false;
}
