#include "Nodes.h"

class NodeStatements: public NonTerminalNode {
public:
	NodeStatements() {
	}
	~NodeStatements() {
	}

	void print(CompilerState &cs) {
		printAllChildren(out);
	}
	static Node* parse(CompilerState &cs);
};
