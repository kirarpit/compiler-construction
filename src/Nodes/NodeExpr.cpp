#include "Nodes/AllNodesHeader.h"

Node* NodeExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::log("Parsing NodeExpr, Token Value: " + lex.peek().value);

	Node *expr = new NodeExpr();

	Node *asgnExpr = NodeAsgnExpr::parse(cs);
	if (asgnExpr) {
		expr->addNode(asgnExpr);
	} else {
		delete expr;
		return NULL;
	}

	while (lex.peek().value == ",") {
		Node *tempExpr = new NodeExpr();

		tempExpr->addNode(expr);
		tempExpr->addNode(new TerminalNode(lex.read()));
		Node *asgnExpr = NodeAsgnExpr::parse(cs);
		if (asgnExpr) {
			tempExpr->addNode(asgnExpr);
		} else {
			delete tempExpr;
			return NULL;
		}

		expr = tempExpr;
	}

	Logger::log("Returning NodeExpr, Token Value: " + lex.peek().value);
	return expr;
}
