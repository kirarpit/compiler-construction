#include "Nodes.h"

class NodeVarName: public NonTerminalNode {
public:
	NodeVarName() {
	}
	~NodeVarName() {
	}

	void print(OutputStream &out) {
		printAllChildren(out);
	}
	static Node* parse(CompilerState &cs);
};
