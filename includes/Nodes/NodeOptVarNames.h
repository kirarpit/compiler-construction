#include "Nodes.h"

class NodeOptVarNames: public NonTerminalNode {
public:
	NodeOptVarNames() {
	}
	~NodeOptVarNames() {
	}

	void print(CompilerState &cs) {
		printAllChildren(out);
	}
	static Node* parse(CompilerState &cs);
};
