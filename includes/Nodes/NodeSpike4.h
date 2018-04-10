#ifndef SRC_NODES_NODESPIKE4_H_
#define SRC_NODES_NODESPIKE4_H_

#include<Node.h>
#include<NonTerminalNode.h>

class CompilerState;

class NodeSpike4: public NonTerminalNode {
public:
	NodeSpike4() {
	}
	~NodeSpike4() {
	}
	void print(CompilerState &cs) = 0;
	static void compile(CompilerState &cs);
	void walk(CompilerState &cs);
};

#endif /* SRC_NODES_NODESPIKE4_H_ */
