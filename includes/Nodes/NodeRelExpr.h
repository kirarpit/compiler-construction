#ifndef SRC_NodeRelExpr_H_
#define SRC_NodeRelExpr_H_

#include "Nodes.h"

class NodeRelExpr: public NonTerminalNode {
public:
	NodeRelExpr() {
	}
	~NodeRelExpr() {
	}

	void print(CompilerState &cs) {
		printFPIF(cs);
	}
	static Node* parse(CompilerState &cs);
};

#endif
