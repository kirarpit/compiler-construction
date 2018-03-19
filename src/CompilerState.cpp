#include"CompilerState.h"

CompilerState::CompilerState(InputStream &in, OutputStream &out,
		ErrorStream &err, Lexer &lex) :
		is(in), os(out), es(err), lexer(lex), lastBlock(NULL) {
}

CompilerState::~CompilerState() {
}
