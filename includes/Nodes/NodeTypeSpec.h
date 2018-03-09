#include "Nodes.h"

class NodeTypeSpec: public NonTerminalNode {
public:
	NodeTypeSpec() {
	}
	~NodeTypeSpec() {
	}

	void print(CompilerState &cs) {
		printAllChildren(cs);
	}
	static Node* parse(CompilerState &cs);
};
