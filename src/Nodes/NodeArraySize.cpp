#include "Nodes/AllNodesHeader.h"

Node* NodeArraySize::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logNodeEntry("NodeArraySize", lex.peek());

	Node *arraySize = new NodeArraySize();

	if (lex.peek().value != TokenTable::TS[TN_clsbrk]) {
		Node *expr = NodeExpr::parse(cs);
		if (expr) {
			arraySize->addNode(expr);
		} else {
			delete arraySize;
			return NULL;
		}
	}

	Logger::logNodeExit("NodeArraySize", lex.peek());
	return arraySize;
}
