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

void NonTerminalNode::smartWalk(CompilerState &cs) {
	walkAllChildren(cs);
	typeProp(cs);
	constFold(cs);
}

void NonTerminalNode::walkAllChildren(CompilerState &cs) {
	for (unsigned int i = 0; i < children.size(); i++) {
		children[i]->walk(cs);

		if (children[i]->isEmpty()) {
			deleteChild(i);
			i--;
		} else {
			Node *temp = reduceBranch(children[i]);
			if (temp)
				children[i] = temp;
		}
	}
}

Node* NonTerminalNode::reduceBranch(Node *node) {
	if (node->isRemovable()) {
		Node *temp = node;
		node = temp->getChild(0);
		temp->clearChildren();
		delete temp;

		return node;
	}

	return NULL;
}

void NonTerminalNode::typeProp(CompilerState &cs) {
	if (children.size() == 1) {
		type = children[0]->getType();

	} else if (children.size() == 3) {
		Logger::log("Type Propagating");

		type = Type::getOperatorType(cs, children[1]->getToken(),
				children[0]->getType(), children[2]->getType());
	}
}

void NonTerminalNode::constFold(CompilerState &cs) {
	if (children.size() == 3) {
		Logger::log("Constant Folding");

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

bool NonTerminalNode::isRemovable() {
	if (children.size() == 1) {
		return true;
	}
	return false;
}

bool NonTerminalNode::isEmpty() {
	if (children.size() == 0) {
		return true;
	}
	return false;
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
