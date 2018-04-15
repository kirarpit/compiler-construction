#ifndef SRC_NodeVarDef_H_
#define SRC_NodeVarDef_H_

#include<NonTerminalNode.h>
class CompilerState;

class NodeVarDef: public NonTerminalNode {
public:
	NodeVarDef() {
	}
	~NodeVarDef() {
	}

	void print(CompilerState &cs) {
	}
	static Node* parse(CompilerState &cs);
	void walk(CompilerState &cs);
	void genCode(CompilerState &cs);
};

#endif
