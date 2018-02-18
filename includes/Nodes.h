#ifndef SRC_NODES_H_
#define SRC_NODES_H_

#include<vector>
#include<OutputStream.h>
#include<Token.h>
#include<Lexer.h>
#include<CompilerState.h>
#include<cstdlib>

using namespace std;

class Node {
public:
	Node() {
	}
	virtual ~Node() {
	}

	virtual void print(OutputStream &) = 0;
	virtual void addNode(Node *node) {
	}
};

class TerminalNode: public Node {
public:
	TerminalNode(Token token) :
			terminalToken(token) {
	}
	~TerminalNode() {
	}

	void print(OutputStream &out) {
		out << terminalToken.value;
	}

	static const bool isTerminal = true;

protected:
	Token terminalToken;
};

class NonTerminalNode: public Node {
public:
	NonTerminalNode() {
	}
	~NonTerminalNode() {
		for (unsigned int i = 0; i < children.size(); i++) {
			delete children[i];
		}
	}

	void print(OutputStream &out) = 0;
	void addNode(Node *node) {
		children.push_back(node);
	}

	static const bool isTerminal = false;

protected:
	vector<Node*> children;
};

class NodeSpike2: public NonTerminalNode {
public:
	NodeSpike2() {
	}
	~NodeSpike2() {
	}

	void print(OutputStream &out) = 0;
	static void parse(CompilerState &cs);
};

class NodeExpr: public NonTerminalNode {
public:
	NodeExpr() {
	}
	~NodeExpr() {
	}

	void print(OutputStream &out);
	static Node* parse(CompilerState &cs);
};

class NodeAsgnExpr: public NonTerminalNode {
public:
	NodeAsgnExpr() {
	}
	~NodeAsgnExpr() {
	}

	void print(OutputStream &out) {
	}
	static Node* parse(CompilerState &cs);
};

class NodePostfixExpr: public NonTerminalNode {
public:
	NodePostfixExpr() {
	}
	~NodePostfixExpr() {
	}

	void print(OutputStream &out) {
	}
	static Node* parse(CompilerState &cs);
};

class NodeCondExpr: public NonTerminalNode {
public:
	NodeCondExpr() {
	}
	~NodeCondExpr() {
	}

	void print(OutputStream &out) {
	}
	static Node* parse(CompilerState &cs);
};

class NodeLogorExpr: public NonTerminalNode {
public:
	NodeLogorExpr() {
	}
	~NodeLogorExpr() {
	}

	void print(OutputStream &out) {
	}
	static Node* parse(CompilerState &cs);
};

class NodeLogandExpr: public NonTerminalNode {
public:
	NodeLogandExpr() {
	}
	~NodeLogandExpr() {
	}

	void print(OutputStream &out) {
	}
	static Node* parse(CompilerState &cs);
};

class NodeEqExpr: public NonTerminalNode {
public:
	NodeEqExpr() {
	}
	~NodeEqExpr() {
	}

	void print(OutputStream &out) {
	}
	static Node* parse(CompilerState &cs);
};

class NodeRelExpr: public NonTerminalNode {
public:
	NodeRelExpr() {
	}
	~NodeRelExpr() {
	}

	void print(OutputStream &out) {
	}
	static Node* parse(CompilerState &cs);
};

class NodeSimpleExpr: public NonTerminalNode {
public:
	NodeSimpleExpr() {
	}
	~NodeSimpleExpr() {
	}

	void print(OutputStream &out) {
	}
	static Node* parse(CompilerState &cs);
};

class NodeTerm: public NonTerminalNode {
public:
	NodeTerm() {
	}
	~NodeTerm() {
	}

	void print(OutputStream &out) {
	}
	static Node* parse(CompilerState &cs);
};

class NodeFactor: public NonTerminalNode {
public:
	NodeFactor() {
	}
	~NodeFactor() {
	}

	void print(OutputStream &out) {
	}
	static Node* parse(CompilerState &cs);
};

class NodePrimaryExpr: public NonTerminalNode {
public:
	NodePrimaryExpr() {
	}
	~NodePrimaryExpr() {
	}

	void print(OutputStream &out) {
	}
	static Node* parse(CompilerState &cs);
};

class NodeArraySpec: public NonTerminalNode {
public:
	NodeArraySpec() {
	}
	~NodeArraySpec() {
	}

	void print(OutputStream &out) {
	}
	static Node* parse(CompilerState &cs);
};

class NodeArraySize: public NonTerminalNode {
public:
	NodeArraySize() {
	}
	~NodeArraySize() {
	}

	void print(OutputStream &out) {
	}
	static Node* parse(CompilerState &cs);
};

#endif /* SRC_NODES_H_ */
