#ifndef SRC_NODES_NODEIFSTMT_H_
#define SRC_NODES_NODEIFSTMT_H_

#include<NonTerminalNode.h>
class CompilerState;

class NodeIfStmt: public NonTerminalNode {
public:
	NodeIfStmt() {
	}
	~NodeIfStmt() {
	}

	static Node* parse(CompilerState &cs);
	void print(CompilerState &cs);
	void walk(CompilerState &cs);
};

#endif /* SRC_NODES_NODEIFSTMT_H_ */
