#ifndef SRC_NODES_NODEOPTIOEXPR_H_
#define SRC_NODES_NODEOPTIOEXPR_H_

#include<NonTerminalNode.h>
class CompilerState;

class NodeOptIOExpr: public NonTerminalNode {
public:
	NodeOptIOExpr() {
	}
	~NodeOptIOExpr() {
	}

	static Node* parse(CompilerState &cs);
	void print(CompilerState &cs);
	void walk(CompilerState &cs);
	Register genCode(CompilerState &cs, CodeGenArgs cg);
};

#endif /* SRC_NODES_NODEOPTIOEXPR_H_ */
