#ifndef SRC_NodeArraySpec_H_
#define SRC_NodeArraySpec_H_

#include "Nodes.h"

class NodeArraySpec: public NonTerminalNode {
public:
	NodeArraySpec() {
	}
	~NodeArraySpec() {
	}

	void print(CompilerState &cs) {
		printAllChildren(cs);
	}
	static Node* parse(CompilerState &cs);
};

#endif
