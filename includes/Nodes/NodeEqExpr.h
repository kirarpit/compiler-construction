#ifndef SRC_NodeEqExpr_H_
#define SRC_NodeEqExpr_H_

class NodeEqExpr: public NonTerminalNode {
public:
	NodeEqExpr() {
	}
	~NodeEqExpr() {
	}

	void print(CompilerState &cs) {
		printFPIF(cs);
	}
	static Node* parse(CompilerState &cs);
};

#endif
