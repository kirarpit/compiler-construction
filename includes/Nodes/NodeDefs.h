#include "Nodes.h"

class NodeDefs: public NonTerminalNode {
public:
	NodeDefs() {
	}
	~NodeDefs() {
	}

	void print(CompilerState &cs) {
		printAllChildren(cs);
	}
	static Node* parse(CompilerState &cs);
};
