#ifndef SRC_NodeTypeSpec_H_
#define SRC_NodeTypeSpec_H_

#include<NonTerminalNode.h>
class CompilerState;

class NodeTypeSpec: public NonTerminalNode {
public:
	NodeTypeSpec() {
	}
	~NodeTypeSpec() {
	}

	void print(CompilerState &cs) {
		printAllChildren(cs);
	}
	static Node* parse(CompilerState &cs);
	void walk(CompilerState &cs);
	void genCode(CompilerState &cs);
};

#endif
