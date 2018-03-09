#include "Nodes.h"

class NodeArraySpecs: public NonTerminalNode {
public:
	NodeArraySpecs() {
	}
	~NodeArraySpecs() {
	}

	void print(CompilerState &cs) {
		printAllChildren(out);
	}
	static Node* parse(CompilerState &cs);
};
