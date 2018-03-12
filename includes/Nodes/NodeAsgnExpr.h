#ifndef SRC_NodeAsgnExpr_H_
#define SRC_NodeAsgnExpr_H_

class NodeAsgnExpr: public NonTerminalNode {
public:
	NodeAsgnExpr() {
	}
	~NodeAsgnExpr() {
	}

	void print(CompilerState &cs) {
		printFPIF(cs);
	}
	static Node* parse(CompilerState &cs);
};

#endif
