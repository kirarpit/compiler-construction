#ifndef SRC_NodePostfixExpr_H_
#define SRC_NodePostfixExpr_H_

#include "Nodes.h"

class NodePostfixExpr: public NonTerminalNode {
public:
	NodePostfixExpr() {
	}
	~NodePostfixExpr() {
	}

	void print(CompilerState &cs) {
		printFPIF(cs);
	}
	static Node* parse(CompilerState &cs);
};

#endif
