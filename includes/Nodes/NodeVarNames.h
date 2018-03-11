#ifndef SRC_NodeVarNames_H_
#define SRC_NodeVarNames_H_

#include "Nodes.h"

class NodeVarNames: public NonTerminalNode {
public:
	NodeVarNames() {
	}
	~NodeVarNames() {
	}

	void print(CompilerState &cs) {
		printAllChildren(cs);
	}
	static Node* parse(CompilerState &cs);
};

#endif
