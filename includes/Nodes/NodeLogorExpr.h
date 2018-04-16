#ifndef SRC_NodeLogorExpr_H_
#define SRC_NodeLogorExpr_H_

#include<NonTerminalNode.h>
class CompilerState;

class NodeLogorExpr: public NonTerminalNode {
public:
	NodeLogorExpr() {
	}
	~NodeLogorExpr() {
	}

	void print(CompilerState &cs) {
		printFPIF(cs);
	}
	static Node* parse(CompilerState &cs);
	void walk(CompilerState &cs);
};

#endif
