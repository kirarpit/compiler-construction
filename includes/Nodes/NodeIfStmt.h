#ifndef SRC_NODES_NODEIFSTMT_H_
#define SRC_NODES_NODEIFSTMT_H_

class NodeIfStmt: public NonTerminalNode {
public:
	NodeIfStmt() {
	}
	~NodeIfStmt() {
	}

	static Node* parse(CompilerState &cs);
	void print(CompilerState &cs);
};

#endif /* SRC_NODES_NODEIFSTMT_H_ */
