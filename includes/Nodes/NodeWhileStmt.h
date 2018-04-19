#ifndef SRC_NODES_NODEWHILESTMT_H_
#define SRC_NODES_NODEWHILESTMT_H_

#include<NonTerminalNode.h>
class CompilerState;

class NodeWhileStmt: public NonTerminalNode {
public:
	NodeWhileStmt() {
	}
	~NodeWhileStmt() {
	}

	static Node* parse(CompilerState &cs);
	void print(CompilerState &cs);
	void walk(CompilerState &cs);
//	void genCode(CompilerState &cs, CodeGenArgs cg);
};

#endif /* SRC_NODES_NODEWHILESTMT_H_ */
