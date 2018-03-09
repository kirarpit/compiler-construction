#include "Nodes.h"

class NodeVarDef: public NonTerminalNode {
public:
	NodeVarDef() {
	}
	~NodeVarDef() {
	}

	void print(CompilerState &cs) {
		printAllChildren(out);
	}
	static Node* parse(CompilerState &cs);
};
