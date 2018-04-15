#ifndef SRC_NodeStatements_H_
#define SRC_NodeStatements_H_

#include<NonTerminalNode.h>
class CompilerState;

class NodeStatements: public NonTerminalNode {
public:
	NodeStatements() {
	}
	~NodeStatements() {
	}

	void print(CompilerState &cs) {
		printAllChildren(cs);
	}
	static Node* parse(CompilerState &cs);
	void walk(CompilerState &cs);
	void genCode(CompilerState &cs);
};

#endif
