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
	static void compile(CompilerState &cs);
	void print(CompilerState &cs) = 0;
	void walk(CompilerState &cs) = 0;
};

#endif /* SRC_NODES_NODESPIKE4_H_ */
