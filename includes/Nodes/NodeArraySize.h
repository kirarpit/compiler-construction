#include "Nodes.h"

class NodeArraySize: public NonTerminalNode {
public:
	NodeArraySize() {
	}
	~NodeArraySize() {
	}

	void print(OutputStream &out) {
		printAllChildren(out);
	}
	static Node* parse(CompilerState &cs);
};
