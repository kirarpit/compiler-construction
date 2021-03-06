#ifndef SRC_NodeTypeName_H_
#define SRC_NodeTypeName_H_

#include<NonTerminalNode.h>
class CompilerState;

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
	void walk(CompilerState &cs);
};

#endif
