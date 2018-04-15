#ifndef SRC_NodeArraySpec_H_
#define SRC_NodeArraySpec_H_

#include<NonTerminalNode.h>
class CompilerState;

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
	void walk(CompilerState &cs);
	void genCode(CompilerState &cs);
};

#endif
