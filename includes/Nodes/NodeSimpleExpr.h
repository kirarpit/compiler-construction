#ifndef SRC_NodeSimpleExpr_H_
#define SRC_NodeSimpleExpr_H_

#include<NonTerminalNode.h>
class CompilerState;

class NodeSimpleExpr: public NonTerminalNode {
public:
	NodeSimpleExpr() {
	}
	~NodeSimpleExpr() {
	}

	void print(CompilerState &cs) {
		printFPIF(cs);
	}
	static Node* parse(CompilerState &cs);
	void walk(CompilerState &cs);
	Register genCode(CompilerState &cs, CodeGenArgs cg);
};

#endif
