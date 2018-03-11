#ifndef SRC_NodeDef_H_
#define SRC_NodeDef_H_

#include "Nodes.h"

class NodeDef: public NonTerminalNode {
public:
	NodeDef() {
	}
	~NodeDef() {
	}

	void print(CompilerState &cs) {
		printAllChildren(cs);
	}
	static Node* parse(CompilerState &cs);
};

#endif
