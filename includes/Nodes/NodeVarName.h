#include "Nodes.h"

class NodeVarName: public NonTerminalNode {
public:
	NodeVarName() {
	}
	~NodeVarName() {
	}

	void print(CompilerState &cs) {
		printAllChildren(out);
	}
	static Node* parse(CompilerState &cs);
};
