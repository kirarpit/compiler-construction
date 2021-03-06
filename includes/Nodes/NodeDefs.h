#ifndef SRC_NodeDefs_H_
#define SRC_NodeDefs_H_

#include<NonTerminalNode.h>
class CompilerState;

class NodeDefs: public NonTerminalNode {
public:
	NodeDefs() {
	}
	~NodeDefs() {
	}

	void print(CompilerState &cs) {
	}
	bool isRemovable() {
		return false;
	}
	static Node* parse(CompilerState &cs);
	void walk(CompilerState &cs);
	Register genCode(CompilerState &cs, CodeGenArgs cg);
};

#endif
