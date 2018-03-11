#ifndef SRC_NodeArraySize_H_
#define SRC_NodeArraySize_H_

#include "Nodes.h"

class NodeArraySize: public NonTerminalNode {
public:
	NodeArraySize() {
	}
	~NodeArraySize() {
	}

	void print(CompilerState &cs) {
		printAllChildren(cs);
	}
	static Node* parse(CompilerState &cs);
};

#endif
