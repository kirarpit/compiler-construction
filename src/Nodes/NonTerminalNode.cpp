#include<NonTerminalNode.h>
#include<CompilerState.h>
#include<OutputStream.h>
#include<Logger.h>

#include<typeinfo>

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

		if (children[i]->getSize() == 0 && children[i]->getST() == NULL) { //implement is empty instead
			Logger::log("Empty Node Deleted");

			deleteChild(i);
			i--;
		} else if (children[i]->getSize() == 1 && children[i]->getST() == NULL) { //implement "is reducable"

			Node *temp = children[i];
			children[i] = temp->getChild(0);
			temp->clearChildren();
			delete temp;
		}
	}

	if (children.size() == 1) {
		type = children[0]->getType();
	}
}

void NonTerminalNode::operatorWalk(CompilerState &cs) {
	if (children.size() == 3) {
		type = Type::getOperandType(cs, children[1]->getToken(),
				children[0]->getType(), children[2]->getType());

		if (children[0]->isConstant && children[2]->isConstant) {
			Node* terminalNode = Type::constantFold(children[1]->getToken(),
					children[0]->getToken(), children[2]->getToken());

			if (terminalNode) {
				terminalNode->setType(type);
				deleteChildren();
				addNode(terminalNode);
			}
		}
	}
}

Node* NonTerminalNode::getChild(int index) {
	return children[index];
}

int NonTerminalNode::getSize() {
	return children.size();
}

void NonTerminalNode::clearChildren() {
	children.clear();
}

void NonTerminalNode::deleteChildren() {
	for (unsigned int i = 0; i < children.size(); i++) {
		delete children[i];
	}
	clearChildren();
}

void NonTerminalNode::deleteChild(int i) {
	delete children[i];
	children.erase(children.begin() + i);
}

void NonTerminalNode::clearChild(int i) {
	children.erase(children.begin() + i);
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
	type->shortPrint(cs);
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
