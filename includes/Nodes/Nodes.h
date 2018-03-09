#ifndef SRC_NODES_H_
#define SRC_NODES_H_

#include<CompilerState.h>
#include<typeinfo>

using namespace std;

class Node {
public:
	Node() {
	}
	virtual ~Node() {
	}

	virtual void print(CompilerState &cs) = 0;
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
		Logger::log("Consumed Terminal:" + token.value);
	}
	~TerminalNode() {
	}

	void print(CompilerState &cs) {
		cs.output << terminalToken.value;
	}

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

	void print(CompilerState &cs) = 0;

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
	void printAllChildren(CompilerState &cs) {
		for (unsigned int i = 0; i < children.size(); i++) {
			children[i]->print(cs);
		}
	}

	void printParenthesised(CompilerState &cs) {
		cs.output << '(';
		printAllChildren(cs);
		cs.output << ')';
	}

	void printFPIF(CompilerState &cs) {
		if (children.size() > 1) {
			printParenthesised(cs);
		} else {
			printAllChildren(cs);
		}
	}

	vector<Node*> children;
};

class NodeSpike3: public NonTerminalNode {
public:
	NodeSpike3() {
	}
	~NodeSpike3() {
	}
	void print(CompilerState &cs) = 0;
	static void parse(CompilerState &cs);
};

#endif /* SRC_NODES_H_ */
