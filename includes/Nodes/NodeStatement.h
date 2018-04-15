#ifndef SRC_NodeStatement_H_
#define SRC_NodeStatement_H_

#include<NonTerminalNode.h>
class CompilerState;

class NodeStatement: public NonTerminalNode {
public:
	NodeStatement() {
	}
	~NodeStatement() {
	}

	void print(CompilerState &cs);
	static Node* parse(CompilerState &cs);
	void walk(CompilerState &cs);
	void genCode(CompilerState &cs);
};

#endif
