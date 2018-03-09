#include "Nodes.h"

class NodeBlock: public NonTerminalNode {
public:
	NodeBlock() :
			myST(NULL) {
	}
	~NodeBlock() {
		delete myST;
	}

	void print(CompilerState &cs) {
		for (unsigned int i = 0; i < children.size(); i++) {
			if (i) {
				children[i]->print(cs);
			}
		}
	}

	void printST(CompilerState &cs) {
		cs.st->print(cs.output);
	}

	void setSymbolTable(SymbolTable *st);
	static Node* parse(CompilerState &cs);

	SymbolTable *myST;
};
