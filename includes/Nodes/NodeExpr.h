#ifndef SRC_NodeExpr_H_
#define SRC_NodeExpr_H_

#include<NonTerminalNode.h>
class CompilerState;

class NodeExpr: public NonTerminalNode {
public:
	NodeExpr() {
	}
	~NodeExpr() {
	}

	void print(CompilerState &cs) {
		printBOTLPIF(cs);
	}
	static Node* parse(CompilerState &cs);
	void walk(CompilerState &cs);
};

#endif
