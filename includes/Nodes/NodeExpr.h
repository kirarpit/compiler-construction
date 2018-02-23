#include "Nodes.h"

class NodeExpr: public NonTerminalNode {
public:
	NodeExpr() {
	}
	~NodeExpr() {
	}

	void print(OutputStream &out) {
		printFPIF(out);
	}
	static Node* parse(CompilerState &cs);
};
