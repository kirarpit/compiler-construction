#ifndef SRC_NodeOptVarNames_H_
#define SRC_NodeOptVarNames_H_

class NodeOptVarNames: public NonTerminalNode {
public:
	NodeOptVarNames() {
	}
	~NodeOptVarNames() {
	}

	void print(CompilerState &cs) {
		printAllChildren(cs);
	}
	static Node* parse(CompilerState &cs);
};

#endif
