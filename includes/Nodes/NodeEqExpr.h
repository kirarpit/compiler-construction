#include "Nodes.h"

class NodeEqExpr: public NonTerminalNode {
public:
	NodeEqExpr() {
	}
	~NodeEqExpr() {
	}

	void print(OutputStream &out) {
		printFPIF(out);
	}
	static Node* parse(CompilerState &cs);
};
