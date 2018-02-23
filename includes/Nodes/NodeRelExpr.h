#include "Nodes.h"

class NodeRelExpr: public NonTerminalNode {
public:
	NodeRelExpr() {
	}
	~NodeRelExpr() {
	}

	void print(OutputStream &out) {
		printFPIF(out);
	}
	static Node* parse(CompilerState &cs);
};
