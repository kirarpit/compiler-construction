#include<ErrorStream.h>
#include<CompilerState.h>
#include<Logger.h>
#include<Lexer.h>
#include<SymbolTable.h>
#include<Node.h>
#include <Type.h>

void ErrorStream::reportParseError(CompilerState &cs) {
	reportError();
	es << "\033[1m" << cs.lexer.peek().stringify()
			<< " \033[1;31merror:\033[0m\033[1m while parsing AST\033[0m"
			<< "\n";
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

void ErrorStream::recover(CompilerState &cs, std::string str) {
	Logger::log("Error Recovery Started: " + str);

	while (cs.lexer.peek().value != TokenTable::TS[TN_semi]
			&& cs.lexer.peek().value != TokenTable::TS[TN_clsbrc]
			&& cs.lexer.peek().type != TT_EOF) {
		cs.lexer.read();
	}

	error = false;
}
