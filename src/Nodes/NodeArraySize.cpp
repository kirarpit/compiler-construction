#include "Nodes/AllNodesHeader.h"

Node* NodeArraySize::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::log(
			"Parsing NodeArraySize, Token Value: " + lex.peek().value);

	Node *arraySize = new NodeArraySize();

	if (lex.peek().value != "]") {
		Node *expr = NodeExpr::parse(cs);
		if (expr) {
			arraySize->addNode(expr);
		} else {
			delete arraySize;
			return NULL;
		}
	}

	Logger::log(
			"Returning NodeArraySize, Token Value: " + lex.peek().value);
	return arraySize;
}
