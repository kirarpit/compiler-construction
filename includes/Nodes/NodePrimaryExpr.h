#ifndef SRC_NodePrimaryExpr_H_
#define SRC_NodePrimaryExpr_H_

#include<NonTerminalNode.h>
class CompilerState;

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
	void walk(CompilerState &cs);
};

#endif
