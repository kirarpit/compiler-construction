#ifndef SRC_NodeEqExpr_H_
#define SRC_NodeEqExpr_H_

#include<NonTerminalNode.h>
class CompilerState;

class NodeEqExpr: public NonTerminalNode {
public:
	NodeEqExpr() {
	}
	~NodeEqExpr() {
	}

	void print(CompilerState &cs) {
		printFPIF(cs);
	}
	static Node* parse(CompilerState &cs);
	void walk(CompilerState &cs);
	void genCode(CompilerState &cs);
};

#endif
