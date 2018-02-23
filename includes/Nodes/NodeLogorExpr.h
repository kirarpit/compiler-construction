#include "Nodes.h"

class NodeLogorExpr: public NonTerminalNode {
public:
	NodeLogorExpr() {
	}
	~NodeLogorExpr() {
	}

	void print(OutputStream &out) {
		printFPIF(out);
	}
	static Node* parse(CompilerState &cs);
};
