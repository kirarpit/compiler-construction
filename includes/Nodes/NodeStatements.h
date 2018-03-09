#include "Nodes.h"

class NodeStatements: public NonTerminalNode {
public:
	NodeStatements() {
	}
	~NodeStatements() {
	}

	void print(CompilerState &cs) {
		printAllChildren(cs);
	}
	static Node* parse(CompilerState &cs);
};
