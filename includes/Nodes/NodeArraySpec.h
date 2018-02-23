#include "Nodes.h"

class NodeArraySpec: public NonTerminalNode {
public:
	NodeArraySpec() {
	}
	~NodeArraySpec() {
	}

	void print(OutputStream &out) {
		printAllChildren(out);
	}
	static Node* parse(CompilerState &cs);
};
