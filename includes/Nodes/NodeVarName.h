#ifndef SRC_NodeVarName_H_
#define SRC_NodeVarName_H_

#include<NonTerminalNode.h>
class CompilerState;

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
	void walk(CompilerState &cs);
};

#endif
