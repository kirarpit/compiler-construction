#include "Nodes.h"
#include "SymbolTable.h"

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

	void print(CompilerState &cs) {
		printST(cs);
		cs.os << '\n';
		for (unsigned int i = 0; i < children.size(); i++) {
			if (i) {
				children[i]->print(cs);
			}
		}
	}

	void printST(CompilerState &cs) {
		myST->print(cs);
	}

	static Node* parse(CompilerState &cs);

	SymbolTable *myST;
};
