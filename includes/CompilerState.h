#ifndef SRC_COMPILERSTATE_H_
#define SRC_COMPILERSTATE_H_

#include<InputStream.h>
#include<OutputStream.h>
#include<Lexer.h>
#include<Logger.h>

using namespace std;

class CompilerState {
public:
	CompilerState(InputStream &in, OutputStream &out, Lexer &lex) :
			input(in), output(out), lexer(lex), error(false), errorCount(0), muteCount(
					0) {
	}
	virtual ~CompilerState() {
	}

	int reportError();
	void muteErrors();
	void unmuteErrors();

	InputStream &input;
	OutputStream &output;
	Lexer &lexer;

	bool error;
private:
	int errorCount;
	int muteCount;
};

#endif /* SRC_COMPILERSTATE_H_ */
