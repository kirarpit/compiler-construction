#include "Nodes.h"

class NodeTypeSpec: public NonTerminalNode {
public:
	NodeTypeSpec() {
	}
	~NodeTypeSpec() {
	}

	void print(CompilerState &cs) {
		printAllChildren(out);
	}
	static Node* parse(CompilerState &cs);
};
