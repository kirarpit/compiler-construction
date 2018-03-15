#ifndef SRC_NODES_NODEWHILESTMT_H_
#define SRC_NODES_NODEWHILESTMT_H_

class NodeWhileStmt: public NonTerminalNode {
public:
	NodeWhileStmt() {
	}
	~NodeWhileStmt() {
	}

	static Node* parse(CompilerState &cs);
	void print(CompilerState &cs) {
	}
};

#endif /* SRC_NODES_NODEWHILESTMT_H_ */
