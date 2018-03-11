#ifndef SRC_NodeSimpleExpr_H_
#define SRC_NodeSimpleExpr_H_

#include "Nodes.h"

class NodeSimpleExpr: public NonTerminalNode {
public:
	NodeSimpleExpr() {
	}
	~NodeSimpleExpr() {
	}

	void print(CompilerState &cs) {
		printFPIF(cs);
	}
	static Node* parse(CompilerState &cs);
};

#endif
