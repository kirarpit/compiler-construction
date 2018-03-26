#ifndef SRC_NodeCondExpr_H_
#define SRC_NodeCondExpr_H_

#include<NonTerminalNode.h>
class CompilerState;

class NodeCondExpr: public NonTerminalNode {
public:
	NodeCondExpr() {
	}
	~NodeCondExpr() {
	}

	void print(CompilerState &cs) {
		printBOTLPIF(cs);
	}
	static Node* parse(CompilerState &cs);
	void walk(CompilerState &cs);
};

#endif
