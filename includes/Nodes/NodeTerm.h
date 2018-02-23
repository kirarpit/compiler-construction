#include "Nodes.h"

class NodeTerm: public NonTerminalNode {
public:
	NodeTerm() {
	}
	~NodeTerm() {
	}

	void print(OutputStream &out) {
		printFPIF(out);
	}
	static Node* parse(CompilerState &cs);
};
