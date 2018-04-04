#ifndef SRC_COMPILERSTATE_H_
#define SRC_COMPILERSTATE_H_

#include<cstdlib>

class Lexer;
class InputStream;
class OutputStream;
class ErrorStream;
class SymbolTable;
class Node;
class TypeFactory;

class CompilerState {
public:
	CompilerState(InputStream &in, OutputStream &out, ErrorStream &err,
			Lexer &lex, TypeFactory &tf);
	virtual ~CompilerState();

	InputStream &is;
	OutputStream &os;
	ErrorStream &es;
	Lexer &lexer;

	TypeFactory &tf;

	Node *lastBlock;
};

#endif /* SRC_COMPILERSTATE_H_ */
