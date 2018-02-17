#ifndef SRC_COMPILERSTATE_H_
#define SRC_COMPILERSTATE_H_

#include<InputStream.h>
#include<OutputStream.h>
#include<Lexer.h>

using namespace std;

class CompilerState {
public:
	CompilerState(InputStream &in, OutputStream &out, Lexer &lex) :
			input(in), output(out), lexer(lex), error(false), errorCount(0) {
	}
	virtual ~CompilerState() {
	}

	int reportError();
	InputStream &input;
	OutputStream &output;
	Lexer &lexer;

	bool error;
private:
	int errorCount;
};

#endif /* SRC_COMPILERSTATE_H_ */