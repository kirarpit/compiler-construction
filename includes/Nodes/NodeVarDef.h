#include "Nodes.h"

class NodeVarDef: public NonTerminalNode {
public:
	NodeVarDef() {
	}
	~NodeVarDef() {
	}

	void print(OutputStream &out) {
		printAllChildren(out);
	}
	static Node* parse(CompilerState &cs);
};