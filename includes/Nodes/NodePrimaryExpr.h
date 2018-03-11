#ifndef SRC_NodePrimaryExpr_H_
#define SRC_NodePrimaryExpr_H_

#include "Nodes.h"

class NodePrimaryExpr: public NonTerminalNode {
public:
	NodePrimaryExpr() {
	}
	~NodePrimaryExpr() {
	}

	void print(CompilerState &cs) {
		printAllChildren(cs);
	}
	static Node* parse(CompilerState &cs);
};

#endif
