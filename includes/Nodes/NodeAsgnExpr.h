#include "Nodes.h"

class NodeAsgnExpr: public NonTerminalNode {
public:
	NodeAsgnExpr() {
	}
	~NodeAsgnExpr() {
	}

	void print(OutputStream &out) {
		printFPIF(out);
	}
	static Node* parse(CompilerState &cs);
};
