#include "Nodes.h"

class NodeArraySize: public NonTerminalNode {
public:
	NodeArraySize() {
	}
	~NodeArraySize() {
	}

	void print(CompilerState &cs) {
		printAllChildren(out);
	}
	static Node* parse(CompilerState &cs);
};
