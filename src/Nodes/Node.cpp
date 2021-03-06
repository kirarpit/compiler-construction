#include<Node.h>
#include<Token.h>
#include<Register.h>
#include<CompilerState.h>
#include<CodeGenArgs.h>

Node::Node() :
		isConstant(false), isTerminal(false), isAssignable(false), type(NULL) {
}

Node::~Node() {
}

void Node::assignable() {
	isAssignable = true;
}

Register Node::genCode(CompilerState &cs, CodeGenArgs cg) {
	return Register(-1);
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

void Node::deleteChildren() {
}

void Node::deleteChild(int index) {
}

Token Node::getToken() {
	return Token();
}

int Node::getSize() {
	return -1;
}

bool Node::isRemovable() {
	return false;
}

bool Node::isEmpty() {
	return false;
}
