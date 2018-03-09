#include "Nodes.h"

class NodeDef: public NonTerminalNode {
public:
	NodeDef() {
	}
	~NodeDef() {
	}

	void print(CompilerState &cs) {
		printAllChildren(out);
	}
	static Node* parse(CompilerState &cs);
};
