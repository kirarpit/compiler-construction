#include "Nodes.h"

class NodeDef: public NonTerminalNode {
public:
	NodeDef() {
	}
	~NodeDef() {
	}

	void print(CompilerState &cs) {
		printAllChildren(cs);
	}
	static Node* parse(CompilerState &cs);
};
