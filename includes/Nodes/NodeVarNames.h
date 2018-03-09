#include "Nodes.h"

class NodeVarNames: public NonTerminalNode {
public:
	NodeVarNames() {
	}
	~NodeVarNames() {
	}

	void print(CompilerState &cs) {
		printAllChildren(cs);
	}
	static Node* parse(CompilerState &cs);
};
