#ifndef SRC_NodeFactor_H_
#define SRC_NodeFactor_H_

#include<NonTerminalNode.h>
class CompilerState;

class NodeFactor: public NonTerminalNode {
public:
	NodeFactor() {
	}
	~NodeFactor() {
	}

	void print(CompilerState &cs) {
		printFPIF(cs);
	}
	static Node* parse(CompilerState &cs);
};

#endif
