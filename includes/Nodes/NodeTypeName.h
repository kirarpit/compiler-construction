#ifndef SRC_NodeTypeName_H_
#define SRC_NodeTypeName_H_

class NodeTypeName: public NonTerminalNode {
public:
	NodeTypeName() {
	}
	~NodeTypeName() {
	}

	void print(CompilerState &cs) {
		printAllChildren(cs);
	}
	static Node* parse(CompilerState &cs);
};

#endif
