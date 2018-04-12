#include<ErrorStream.h>
#include<CompilerState.h>
#include<Logger.h>
#include<Lexer.h>
#include<SymbolTable.h>
#include<Node.h>
#include<Type.h>
#include<Token.h>

void ErrorStream::printErrorEnd() {
	es << "\033[0m";
	es << "\n";
}

void ErrorStream::printTokenError(Token t) {
	es << "\033[1m" << t.stringify() << " \033[1;31m" << "error: " << "\033[0m"
			<< "\033[1m";
}

void ErrorStream::reportParseError(CompilerState &cs, std::string message) {
	reportError();
	printTokenError(cs.lexer.peek());

	if (message != "") {
		es << message;
	}

	printErrorEnd();
}

void ErrorStream::reportDeclError(CompilerState &cs, Token t) {
	reportError();
	printTokenError(t);

	if (cs.lastBlock->getST()->isDef)
		es << "redefinition of" << " '" << t.value << "'";
	else
		es << "use of undeclared identifier" << " '" << t.value << "'";

	printErrorEnd();
}

void ErrorStream::reportError() {
	Logger::log("Error Reported: Total error count: %d", errorCount + 1);

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
