#ifndef SRC_NodePostfixExpr_H_
#define SRC_NodePostfixExpr_H_

#include<NonTerminalNode.h>
class CompilerState;

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
	void walk(CompilerState &cs);
	Register genCode(CompilerState &cs, CodeGenArgs cg);
};

#endif
