#include<NonTerminalNode.h>
#include<CompilerState.h>

NonTerminalNode::NonTerminalNode() {
}

NonTerminalNode::~NonTerminalNode() {
	for (unsigned int i = 0; i < children.size(); i++) {
		delete children[i];
	}
}

void NonTerminalNode::addNode(Node *node) {
	children.push_back(node);
}

void NonTerminalNode::walk(CompilerState &cs) {
	for (unsigned int i = 0; i < children.size(); i++) {
		children[i]->walk(cs);
	}
}

bool NonTerminalNode::findPostfixExpr() {
	if (getName() == "15NodePostfixExpr")
		return true;
	if (children.size() != 1)
		return false;

	return children[0]->findPostfixExpr();
}

std::string NonTerminalNode::getName() {
	return std::string("") + typeid(*this).name();
}

void NonTerminalNode::printAllChildren(CompilerState &cs) {
	for (unsigned int i = 0; i < children.size(); i++) {
		children[i]->print(cs);
	}
}

void NonTerminalNode::printParenthesised(CompilerState &cs) {
	cs.os << '(';
	printAllChildren(cs);
	cs.os << ')';
}

void NonTerminalNode::printFPIF(CompilerState &cs) {
	if (children.size() > 1) {
		printParenthesised(cs);
	} else {
		printAllChildren(cs);
	}
}
