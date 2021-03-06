#ifndef SRC_NodeVarNames_H_
#define SRC_NodeVarNames_H_

#include<NonTerminalNode.h>
class CompilerState;

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
	void walk(CompilerState &cs);
};

#endif
