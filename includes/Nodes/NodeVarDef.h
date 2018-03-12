#ifndef SRC_NodeVarDef_H_
#define SRC_NodeVarDef_H_

class NodeVarDef: public NonTerminalNode {
public:
	NodeVarDef() {
	}
	~NodeVarDef() {
	}

	void print(CompilerState &cs) {
		printAllChildren(cs);
	}
	static Node* parse(CompilerState &cs);
};

#endif
