#ifndef SRC_NodeOptVarNames_H_
#define SRC_NodeOptVarNames_H_

#include<NonTerminalNode.h>
class CompilerState;

class NodeOptVarNames: public NonTerminalNode {
public:
	NodeOptVarNames() {
	}
	~NodeOptVarNames() {
	}

	void print(CompilerState &cs) {
		printAllChildren(cs);
	}
	static Node* parse(CompilerState &cs);
	void walk(CompilerState &cs);
	void genCode(CompilerState &cs);
};

#endif
