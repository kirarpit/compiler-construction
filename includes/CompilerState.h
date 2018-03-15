#ifndef SRC_COMPILERSTATE_H_
#define SRC_COMPILERSTATE_H_

#include<cstdlib>

#include<Lexer.h>
#include<OutputStream.h>
class ErrorStream;
class SymbolTable;
class Node;

class CompilerState {
public:
	CompilerState(InputStream &in, OutputStream &out, ErrorStream &err,
			Lexer &lex) :
			is(in), os(out), es(err), lexer(lex), st(NULL), crntBlk(NULL) {
	}
	virtual ~CompilerState() {
	}

	InputStream &is;
	OutputStream &os;
	ErrorStream &es;
	Lexer &lexer;
	SymbolTable *st;
	Node *crntBlk;
};

#endif /* SRC_COMPILERSTATE_H_ */
