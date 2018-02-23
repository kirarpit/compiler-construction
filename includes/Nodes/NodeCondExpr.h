#include "Nodes.h"

class NodeCondExpr: public NonTerminalNode {
public:
	NodeCondExpr() {
	}
	~NodeCondExpr() {
	}

	void print(OutputStream &out) {
		printFPIF(out);
	}
	static Node* parse(CompilerState &cs);
};
