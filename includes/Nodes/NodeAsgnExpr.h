#ifndef SRC_NodeAsgnExpr_H_
#define SRC_NodeAsgnExpr_H_

#include<NonTerminalNode.h>
class CompilerState;

class NodeAsgnExpr: public NonTerminalNode {
public:
	NodeAsgnExpr() {
	}
	~NodeAsgnExpr() {
	}

	void print(CompilerState &cs) {
		printFPIF(cs);
	}
	static Node* parse(CompilerState &cs);
	void walk(CompilerState &cs);
	Register genCode(CompilerState &cs, CodeGenArgs cg);
};

#endif
