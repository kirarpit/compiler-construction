#include "Nodes.h"

class NodeDef: public NonTerminalNode {
public:
	NodeDef() {
	}
	~NodeDef() {
	}

	void print(OutputStream &out) {
		printAllChildren(out);
	}
	static Node* parse(CompilerState &cs);
};
