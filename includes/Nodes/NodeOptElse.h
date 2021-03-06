#ifndef SRC_NODES_NODEOPTELSE_H_
#define SRC_NODES_NODEOPTELSE_H_

#include<NonTerminalNode.h>
class CompilerState;

class NodeOptElse: public NonTerminalNode {
public:
	NodeOptElse() {
	}
	~NodeOptElse() {
	}

	static Node* parse(CompilerState &cs);
	void print(CompilerState &cs);
	void walk(CompilerState &cs);
	Register genCode(CompilerState &cs, CodeGenArgs cg);
};

#endif /* SRC_NODES_NODEOPTELSE_H_ */
