#include "Nodes.h"

class NodeSimpleExpr: public NonTerminalNode {
public:
	NodeSimpleExpr() {
	}
	~NodeSimpleExpr() {
	}

	void print(OutputStream &out) {
		printFPIF(out);
	}
	static Node* parse(CompilerState &cs);
};
