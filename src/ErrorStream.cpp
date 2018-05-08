#include<ErrorStream.h>
#include<CompilerState.h>
#include<Logger.h>
#include<Lexer.h>
#include<SymbolTable.h>
#include<Node.h>
#include<Type.h>
#include<Token.h>
#include<OutputStream.h>

void ErrorStream::printErrorEnd() {
	es << "\033[0m";
	es << "\n";
}

void ErrorStream::printTokenError(Token t) {
	es << "\033[1m" << t.stringify() << " \033[1;31m" << "error: " << "\033[0m"
			<< "\033[1m";
}

void ErrorStream::reportError(CompilerState &cs, std::string message) {
	incrErrorCnt();
	printTokenError(cs.lexer.peek());

	if (message != "") {
		es << message;
	}

	printErrorEnd();
}

void ErrorStream::reportDeclError(CompilerState &cs, Token t) {
	incrErrorCnt();
	printTokenError(t);

	if (cs.lastBlock->getST()->isDef)
		es << "redefinition of" << " '" << t.value << "'";
	else
		es << "use of undeclared identifier" << " '" << t.value << "'";

	printErrorEnd();
}

void ErrorStream::reportTypeError(CompilerState &cs, Token t, Type *type,
		std::string message) {
	incrErrorCnt();
	printTokenError(t);

	es << replaceType(cs, message, "%t", type);

	printErrorEnd();
}

void ErrorStream::reportOpTypeError(CompilerState &cs, Token t, Type *type1,
		Type *type2, std::string message) {
	incrErrorCnt();
	printTokenError(t);

	message = replaceType(cs, message, "%t1", type1);
	es << replaceType(cs, message, "%t2", type2);

	printErrorEnd();
}

std::string ErrorStream::replaceType(CompilerState &cs, std::string message,
		std::string replace, Type *type) {
	if (message.find(replace) != std::string::npos) {
		cs.os.startBuffer();
		type->print(cs);
		std::string typeS = cs.os.clearBuffer();

		message.replace(message.find(replace), std::string(replace).length(),
				typeS);
	}

	return message;
}

void ErrorStream::incrErrorCnt() {
	Logger::log("Error Reported: Total error count: %d", errorCount + 1);

	error = true;
	++errorCount;
	if (errorCount == 100) {
		es << "\n\t\tI'll have what you're having! ¯\\_(ツ)_/¯ \n\n";
		exit(100);
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
