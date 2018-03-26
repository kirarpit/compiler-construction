#ifndef SRC_NodeArraySpecs_H_
#define SRC_NodeArraySpecs_H_

#include<NonTerminalNode.h>
class CompilerState;

class NodeOptArraySpecs: public NonTerminalNode {
public:
	NodeOptArraySpecs() {
	}
	~NodeOptArraySpecs() {
	}

	void print(CompilerState &cs) {
		printAllChildren(cs);
	}
	static Node* parse(CompilerState &cs);
};

#endif
