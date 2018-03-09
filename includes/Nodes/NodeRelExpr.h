#include "Nodes.h"

class NodeRelExpr: public NonTerminalNode {
public:
	NodeRelExpr() {
	}
	~NodeRelExpr() {
	}

	void print(CompilerState &cs) {
		printFPIF(out);
	}
	static Node* parse(CompilerState &cs);
};
