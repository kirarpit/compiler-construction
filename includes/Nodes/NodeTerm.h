#include "Nodes.h"

class NodeTerm: public NonTerminalNode {
public:
	NodeTerm() {
	}
	~NodeTerm() {
	}

	void print(CompilerState &cs) {
		printFPIF(out);
	}
	static Node* parse(CompilerState &cs);
};
