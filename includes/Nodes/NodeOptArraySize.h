#ifndef SRC_NodeArraySize_H_
#define SRC_NodeArraySize_H_

#include<NonTerminalNode.h>
class CompilerState;

class NodeOptArraySize: public NonTerminalNode {
public:
	NodeOptArraySize() {
	}
	~NodeOptArraySize() {
	}

	void print(CompilerState &cs) {
		printAllChildren(cs);
	}
	static Node* parse(CompilerState &cs);
	void walk(CompilerState &cs);
	void genCode(CompilerState &cs);
};

#endif
