#ifndef SRC_NodeArraySize_H_
#define SRC_NodeArraySize_H_

#include<NonTerminalNode.h>
class CompilerState;

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
