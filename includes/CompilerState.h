#ifndef SRC_COMPILERSTATE_H_
#define SRC_COMPILERSTATE_H_

#include<OutputStream.h>
#include<Lexer.h>
#include<Logger.h>
#include<cstdlib>

class SymbolTable;

class CompilerState {
public:
	CompilerState(InputStream &in, OutputStream &out, Lexer &lex) :
			input(in), output(out), lexer(lex), st(
			NULL), error(false), errorCount(0) {
	}
	virtual ~CompilerState() {
	}

	void reportError();
	int getErrorCount();
	void recover();

	InputStream &input;
	OutputStream &output;
	Lexer &lexer;
	SymbolTable *st;

	bool error;
private:
	int errorCount;
};

#endif /* SRC_COMPILERSTATE_H_ */
