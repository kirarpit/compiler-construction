#ifndef SRC_NodeDefs_H_
#define SRC_NodeDefs_H_

class NodeDefs: public NonTerminalNode {
public:
	NodeDefs() {
	}
	~NodeDefs() {
	}

	void print(CompilerState &cs) {
		printAllChildren(cs);
	}
	static Node* parse(CompilerState &cs);
};

#endif
