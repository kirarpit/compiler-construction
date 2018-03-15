#ifndef SRC_NodeStatement_H_
#define SRC_NodeStatement_H_

class NodeStatement: public NonTerminalNode {
public:
	NodeStatement() {
	}
	~NodeStatement() {
	}

	void print(CompilerState &cs);
	static Node* parse(CompilerState &cs);
};

#endif
