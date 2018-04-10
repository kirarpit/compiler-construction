#include<NodeExpr.h>
#include <NodeOptArraySize.h>

Node* NodeOptArraySize::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

	Node *arraySize = new NodeOptArraySize();

	if (lex.peek().value != TokenTable::TS[TN_clsbrk]) {
		Node *expr = NodeExpr::parse(cs);
		if (expr) {
			arraySize->addNode(expr);
		} else {
			delete arraySize;
			return NULL;
		}
	}

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return arraySize;
}

void NodeOptArraySize::walk(CompilerState &cs) {
	Logger::logWalkEntry(__CLASS_NAME__, this);

	smartWalk(cs);

	Logger::logWalkExit(__CLASS_NAME__, this);
}
