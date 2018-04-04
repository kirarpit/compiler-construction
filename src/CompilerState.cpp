#include"CompilerState.h"

CompilerState::CompilerState(InputStream &in, OutputStream &out,
		ErrorStream &err, Lexer &lex, TypeFactory &tf) :
		is(in), os(out), es(err), lexer(lex), tf(tf), lastBlock(NULL) {
}

CompilerState::~CompilerState() {
}
