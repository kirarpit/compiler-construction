#include "Nodes.h"

class NodePostfixExpr: public NonTerminalNode {
public:
	NodePostfixExpr() {
	}
	~NodePostfixExpr() {
	}

	void print(CompilerState &cs) {
		printFPIF(out);
	}
	static Node* parse(CompilerState &cs);
};
