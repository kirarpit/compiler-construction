#ifndef SRC_NodeExpr_H_
#define SRC_NodeExpr_H_

class NodeExpr: public NonTerminalNode {
public:
	NodeExpr() {
	}
	~NodeExpr() {
	}

	void print(CompilerState &cs) {
		printFPIF(cs);
	}
	static Node* parse(CompilerState &cs);
};

#endif
