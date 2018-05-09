#ifndef SRC_NODES_NODEIOVAR_H_
#define SRC_NODES_NODEIOVAR_H_

#include<NonTerminalNode.h>
class CompilerState;

class NodeIOVar: public NonTerminalNode {
public:
	NodeIOVar() {
	}
	~NodeIOVar() {
	}

	static Node* parse(CompilerState &cs);
	void print(CompilerState &cs);
	void walk(CompilerState &cs);
	Register genCode(CompilerState &cs, CodeGenArgs cg);
};

#endif /* SRC_NODES_NODEIOVAR_H_ */
