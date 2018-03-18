#ifndef SRC_NodeBlock_H_
#define SRC_NodeBlock_H_

#include<SymbolTable.h>

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

	void print(CompilerState &cs);
	void printST(CompilerState &cs);
	static Node* parse(CompilerState &cs);
	SymbolTable* getST();

	SymbolTable *myST;
};

#endif
