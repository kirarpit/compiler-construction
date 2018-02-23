#include "Nodes.h"

class NodeLogandExpr: public NonTerminalNode {
public:
	NodeLogandExpr() {
	}
	~NodeLogandExpr() {
	}

	void print(OutputStream &out) {
		printFPIF(out);
	}
	static Node* parse(CompilerState &cs);
};
