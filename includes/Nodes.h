#ifndef SRC_NODES_H_
#define SRC_NODES_H_

#include<vector>
#include<OutputStream.h>
#include<Token.h>
#include<Lexer.h>
#include<CompilerState.h>

using namespace std;

class Node {
public:
	virtual ~Node();
	virtual void print(OutputStream &) = 0;
	void addNode(Node *node);
};

class TerminalNode: public Node {
public:
	TerminalNode(Token token) :
			terminalToken(token) {
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
	virtual ~NonTerminalNode() {
		for (unsigned int i = 0; i < children.size(); i++) {
			delete children[i];
		}
	}
	void print(OutputStream &out);
	void addNode(Node *node) {
		children.push_back(node);
	}
	static const bool isTerminal = false;

protected:
	vector<Node*> children;
};

class NodeSpike2: public NonTerminalNode {
public:
	~NodeSpike2() {
	}
	void print(OutputStream &out);
	static void parse(CompilerState &cs);
};

class NodeExpr: public NonTerminalNode {
public:
	~NodeExpr() {
	}
	void print(OutputStream &out);
	static Node* parse(CompilerState &cs);
};

class NodeAsgnExpr: public NonTerminalNode {
public:
	~NodeAsgnExpr() {
	}
	void print(OutputStream &out);
	static Node* parse(CompilerState &cs);
};

#endif /* SRC_NODES_H_ */
