#include "Nodes.h"

class NodeDefs: public NonTerminalNode {
public:
	NodeDefs() {
	}
	~NodeDefs() {
	}

	void print(CompilerState &cs) {
		printAllChildren(out);
	}
	static Node* parse(CompilerState &cs);
};
