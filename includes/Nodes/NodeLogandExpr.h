#include "Nodes.h"

class NodeLogandExpr: public NonTerminalNode {
public:
	NodeLogandExpr() {
	}
	~NodeLogandExpr() {
	}

	void print(CompilerState &cs) {
		printFPIF(out);
	}
	static Node* parse(CompilerState &cs);
};
