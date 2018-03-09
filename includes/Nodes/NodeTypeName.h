#include "Nodes.h"

class NodeTypeName: public NonTerminalNode {
public:
	NodeTypeName() {
	}
	~NodeTypeName() {
	}

	void print(CompilerState &cs) {
		printAllChildren(out);
	}
	static Node* parse(CompilerState &cs);
};
