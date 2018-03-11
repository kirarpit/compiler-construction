#ifndef SRC_NodeLogandExpr_H_
#define SRC_NodeLogandExpr_H_

#include "Nodes.h"

class NodeLogandExpr: public NonTerminalNode {
public:
	NodeLogandExpr() {
	}
	~NodeLogandExpr() {
	}

	void print(CompilerState &cs) {
		printFPIF(cs);
	}
	static Node* parse(CompilerState &cs);
};

#endif
