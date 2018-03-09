#include "Nodes.h"

class NodeEqExpr: public NonTerminalNode {
public:
	NodeEqExpr() {
	}
	~NodeEqExpr() {
	}

	void print(CompilerState &cs) {
		printFPIF(out);
	}
	static Node* parse(CompilerState &cs);
};
