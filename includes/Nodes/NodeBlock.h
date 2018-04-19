#ifndef SRC_NodeBlock_H_
#define SRC_NodeBlock_H_

#include<NonTerminalNode.h>
class CompilerState;
class SymbolTable;

class NodeBlock: public NonTerminalNode {
public:
	NodeBlock() :
			myST(NULL) {
	}
	NodeBlock(SymbolTable *st) :
			myST(st) {
	}
	~NodeBlock() {
		delete myST;
	}

	bool isRemovable();
	bool isEmpty();
	void print(CompilerState &cs);
	void printST(CompilerState &cs);
	static Node* parse(CompilerState &cs);
	void walk(CompilerState &cs);
	Register genCode(CompilerState &cs, CodeGenArgs cg);
	SymbolTable* getST();

	SymbolTable *myST;
};

#endif
