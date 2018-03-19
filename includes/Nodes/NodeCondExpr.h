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
		printFPIF(cs);
	}
	static Node* parse(CompilerState &cs);
};

#endif
