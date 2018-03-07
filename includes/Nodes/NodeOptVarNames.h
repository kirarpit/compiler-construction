#include "Nodes.h"

class NodeOptVarNames: public NonTerminalNode {
public:
	NodeOptVarNames() {
	}
	~NodeOptVarNames() {
	}

	void print(OutputStream &out) {
		printAllChildren(out);
	}
	static Node* parse(CompilerState &cs);
};
