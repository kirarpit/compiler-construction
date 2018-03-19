#include<Node.h>

Node::Node() :
		type(NULL) {
}

Node::~Node() {
}

void Node::addNode(Node *node) {
}

bool Node::findPostfixExpr() {
	return false;
}

SymbolTable* Node::getST() {
	return NULL;
}

TypeInfo* Node::getType() {
	return type;
}
