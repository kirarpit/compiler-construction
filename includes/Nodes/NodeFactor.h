#include "Nodes.h"

class NodeFactor: public NonTerminalNode {
public:
	NodeFactor() {
	}
	~NodeFactor() {
	}

	void print(OutputStream &out) {
		printFPIF(out);
	}
	static Node* parse(CompilerState &cs);
};
