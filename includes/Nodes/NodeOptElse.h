#ifndef SRC_NODES_NODEOPTELSE_H_
#define SRC_NODES_NODEOPTELSE_H_

class NodeOptElse: public NonTerminalNode {
public:
	NodeOptElse() {
	}
	~NodeOptElse() {
	}

	static Node* parse(CompilerState &cs);
	void print(CompilerState &cs) {
	}
};

#endif /* SRC_NODES_NODEOPTELSE_H_ */
