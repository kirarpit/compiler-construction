#include "Nodes.h"

class NodeCondExpr: public NonTerminalNode {
public:
	NodeCondExpr() {
	}
	~NodeCondExpr() {
	}

	void print(CompilerState &cs) {
		printFPIF(out);
	}
	static Node* parse(CompilerState &cs);
};
