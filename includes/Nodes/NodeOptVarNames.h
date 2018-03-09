#include "Nodes.h"

class NodeOptVarNames: public NonTerminalNode {
public:
	NodeOptVarNames() {
	}
	~NodeOptVarNames() {
	}

	void print(CompilerState &cs) {
		printAllChildren(cs);
	}
	static Node* parse(CompilerState &cs);
};
