#ifndef SRC_NodeLogorExpr_H_
#define SRC_NodeLogorExpr_H_

class NodeLogorExpr: public NonTerminalNode {
public:
	NodeLogorExpr() {
	}
	~NodeLogorExpr() {
	}

	void print(CompilerState &cs) {
		printFPIF(cs);
	}
	static Node* parse(CompilerState &cs);
};

#endif
