#ifndef SRC_NodeLogandExpr_H_
#define SRC_NodeLogandExpr_H_

#include<NonTerminalNode.h>
class CompilerState;

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
	void walk(CompilerState &cs);
	Register genCode(CompilerState &cs, CodeGenArgs cg);
};

#endif
