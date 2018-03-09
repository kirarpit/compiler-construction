#include "Nodes.h"

class NodeSimpleExpr: public NonTerminalNode {
public:
	NodeSimpleExpr() {
	}
	~NodeSimpleExpr() {
	}

	void print(CompilerState &cs) {
		printFPIF(out);
	}
	static Node* parse(CompilerState &cs);
};
