#include "Nodes.h"

class NodeVarNames: public NonTerminalNode {
public:
	NodeVarNames() {
	}
	~NodeVarNames() {
	}

	void print(CompilerState &cs) {
		printAllChildren(out);
	}
	static Node* parse(CompilerState &cs);
};
