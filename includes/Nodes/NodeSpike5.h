#ifndef SRC_NODES_NODESPIKE4_H_
#define SRC_NODES_NODESPIKE4_H_

#include<Node.h>
#include<NonTerminalNode.h>

class CompilerState;

class NodeSpike5: public NonTerminalNode {
public:
	NodeSpike5() {
	}
	~NodeSpike5() {
	}
	void print(CompilerState &cs) = 0;
	static void compile(CompilerState &cs);
	void walk(CompilerState &cs);
	void genCode(CompilerState &cs);
};

#endif /* SRC_NODES_NODESPIKE4_H_ */
