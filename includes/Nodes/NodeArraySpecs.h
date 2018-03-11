#ifndef SRC_NodeArraySpecs_H_
#define SRC_NodeArraySpecs_H_

#include "Nodes.h"

class NodeArraySpecs: public NonTerminalNode {
public:
	NodeArraySpecs() {
	}
	~NodeArraySpecs() {
	}

	void print(CompilerState &cs) {
		printAllChildren(cs);
	}
	static Node* parse(CompilerState &cs);
};

#endif
