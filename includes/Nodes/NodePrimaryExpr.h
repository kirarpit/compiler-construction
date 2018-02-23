#include "Nodes.h"

class NodePrimaryExpr: public NonTerminalNode {
public:
	NodePrimaryExpr() {
	}
	~NodePrimaryExpr() {
	}

	void print(OutputStream &out) {
		printAllChildren(out);
	}
	static Node* parse(CompilerState &cs);
};
