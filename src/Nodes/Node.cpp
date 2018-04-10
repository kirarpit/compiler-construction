#include<Node.h>
#include<Token.h>

Node::Node() :
		isConstant(false), isTerminal(false), type(NULL) {
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

Type* Node::getType() {
	return type;
}

void Node::setType(Type *t) {
	type = t;
}

Node* Node::getChild(int index) {
	return NULL;
}

void Node::clearChildren() {
}

void Node::deleteChild(int index){
}

Token Node::getToken() {
	return Token();
}

int Node::getSize() {
	return -1;
}
