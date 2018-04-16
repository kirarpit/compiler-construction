#include"CompilerState.h"

CompilerState::CompilerState(InputStream &in, OutputStream &out,
		ErrorStream &err, Lexer &lex, TypeFactory &tf, RegisterFactory &rf,
		CodeGenArgs &cg) :
		is(in), os(out), es(err), lexer(lex), tf(tf), rf(rf), cg(cg), lastBlock(
				NULL) {
}

CompilerState::~CompilerState() {
}
