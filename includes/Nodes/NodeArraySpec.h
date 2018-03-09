#include "Nodes.h"

class NodeArraySpec: public NonTerminalNode {
public:
	NodeArraySpec() {
	}
	~NodeArraySpec() {
	}

	void print(CompilerState &cs) {
		printAllChildren(out);
	}
	static Node* parse(CompilerState &cs);
};
