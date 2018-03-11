#ifndef SRC_NodeTypeName_H_
#define SRC_NodeTypeName_H_

#include "Nodes.h"

class NodeTypeName: public NonTerminalNode {
public:
	NodeTypeName() {
	}
	~NodeTypeName() {
	}

	void print(CompilerState &cs) {
		printAllChildren(cs);
	}
	static Node* parse(CompilerState &cs);
};

#endif
