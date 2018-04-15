#ifndef SRC_NodeRelExpr_H_
#define SRC_NodeRelExpr_H_

#include<NonTerminalNode.h>
class CompilerState;

class NodeRelExpr: public NonTerminalNode {
public:
	NodeRelExpr() {
	}
	~NodeRelExpr() {
	}

	void print(CompilerState &cs) {
		printFPIF(cs);
	}
	static Node* parse(CompilerState &cs);
	void walk(CompilerState &cs);
	void genCode(CompilerState &cs);
};

#endif
