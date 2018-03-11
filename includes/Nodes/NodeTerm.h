#ifndef SRC_NodeTerm_H_
#define SRC_NodeTerm_H_

#include "Nodes.h"

class NodeTerm: public NonTerminalNode {
public:
	NodeTerm() {
	}
	~NodeTerm() {
	}

	void print(CompilerState &cs) {
		printFPIF(cs);
	}
	static Node* parse(CompilerState &cs);
};

#endif
