#ifndef SRC_NODES_NODEIOSTMT_H_
#define SRC_NODES_NODEIOSTMT_H_

#include<NonTerminalNode.h>
class CompilerState;

class NodeIOExpr: public NonTerminalNode {
public:
	NodeIOExpr() {
	}
	~NodeIOExpr() {
	}

	static Node* parse(CompilerState &cs);
	void print(CompilerState &cs);
	void walk(CompilerState &cs);
	Register genCode(CompilerState &cs, CodeGenArgs cg);
};

#endif /* SRC_NODES_NODEIOSTMT_H_ */
