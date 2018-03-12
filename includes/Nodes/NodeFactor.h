#ifndef SRC_NodeFactor_H_
#define SRC_NodeFactor_H_

class NodeFactor: public NonTerminalNode {
public:
	NodeFactor() {
	}
	~NodeFactor() {
	}

	void print(CompilerState &cs) {
		printFPIF(cs);
	}
	static Node* parse(CompilerState &cs);
};

#endif
