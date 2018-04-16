#ifndef SRC_NodeTerm_H_
#define SRC_NodeTerm_H_

#include<NonTerminalNode.h>
class CompilerState;

class NodeTerm: public NonTerminalNode {
public:
	NodeTerm() {
	}
	~NodeTerm() {
	}

	void print(CompilerState &cs) {
		printFPIF(cs);
	}
	static Node* parse(CompilerState &cs);
	void walk(CompilerState &cs);
	Register genCode(CompilerState &cs);
};

#endif
