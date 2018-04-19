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
class RegisterFactory;
class CodeGenArgs;

class CompilerState {
public:
	CompilerState(InputStream &in, OutputStream &out, ErrorStream &err,
			Lexer &lex, TypeFactory &tf, RegisterFactory &rf);
	virtual ~CompilerState();

	InputStream &is;
	OutputStream &os;
	ErrorStream &es;
	Lexer &lexer;

	TypeFactory &tf;
	RegisterFactory &rf;

	Node *lastBlock;
};

#endif /* SRC_COMPILERSTATE_H_ */
