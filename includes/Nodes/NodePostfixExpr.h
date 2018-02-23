#include "Nodes.h"

class NodePostfixExpr: public NonTerminalNode {
public:
	NodePostfixExpr() {
	}
	~NodePostfixExpr() {
	}

	void print(OutputStream &out) {
		printFPIF(out);
	}
	static Node* parse(CompilerState &cs);
};
