#include"CompilerState.h"

CompilerState::CompilerState(InputStream &in, OutputStream &out,
		ErrorStream &err, Lexer &lex, TypeFactory &tf, RegisterFactory &rf) :
		is(in), os(out), es(err), lexer(lex), tf(tf), rf(rf), lastBlock(
		NULL) {
}

CompilerState::~CompilerState() {
}
