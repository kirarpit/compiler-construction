#ifndef SRC_NodeArraySpecs_H_
#define SRC_NodeArraySpecs_H_

#include<NonTerminalNode.h>
class CompilerState;

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
