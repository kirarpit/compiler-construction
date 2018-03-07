#ifndef SRC_NODES_H_
#define SRC_NODES_H_

#include "CompilerState.h"
#include<typeinfo>

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

	virtual bool findPostfixExpr() {
		return false;
	}
};

class TerminalNode: public Node {
public:
	TerminalNode(Token token) :
			terminalToken(token) {
		Logger::log("Consumed Terminal:" + token.value + "\n");
	}
	~TerminalNode() {
	}

	void print(OutputStream &out) {
		out << terminalToken.value;
	}

protected:
	Token terminalToken;
};

class NonTerminalNode: public Node {
public:
	NonTerminalNode() :
			st(NULL) {
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

	bool findPostfixExpr() {
		if (getName() == "15NodePostfixExpr")
			return true;
		if (children.size() != 1)
			return false;

		return children[0]->findPostfixExpr();
	}

	string getName() {
		return string("") + typeid(*this).name();
	}

protected:
	void printAllChildren(OutputStream &out) {
		for (unsigned int i = 0; i < children.size(); i++) {
			children[i]->print(out);
		}
	}

	void printParenthesised(OutputStream &out) {
		out << '(';
		printAllChildren(out);
		out << ')';
	}

	void printFPIF(OutputStream &out) {
		if (children.size() > 1) {
			printParenthesised(out);
		} else {
			printAllChildren(out);
		}
	}

	vector<Node*> children;
	SymbolTable *st;
};

class NodeSpike3: public NonTerminalNode {
public:
	NodeSpike3() {
	}
	~NodeSpike3() {
	}
	void print(OutputStream &out) = 0;
	static void parse(CompilerState &cs);
};

#endif /* SRC_NODES_H_ */
