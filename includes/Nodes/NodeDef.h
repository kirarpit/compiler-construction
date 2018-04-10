#ifndef SRC_NodeDef_H_
#define SRC_NodeDef_H_

#include<NonTerminalNode.h>
class CompilerState;

class NodeDef: public NonTerminalNode {
public:
	NodeDef() {
	}
	~NodeDef() {
	}

	void print(CompilerState &cs) {
	}
	static Node* parse(CompilerState &cs);
	void walk(CompilerState &cs);
};

#endif
