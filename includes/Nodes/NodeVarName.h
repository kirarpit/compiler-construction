#ifndef SRC_NodeVarName_H_
#define SRC_NodeVarName_H_

#include "Nodes.h"

class NodeVarName: public NonTerminalNode {
public:
	NodeVarName() {
	}
	~NodeVarName() {
	}

	void print(CompilerState &cs) {
		printAllChildren(cs);
	}
	static Node* parse(CompilerState &cs);
};

#endif
