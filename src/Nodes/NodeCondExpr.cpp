#include "Nodes/AllNodesHeader.h"

Node* NodeCondExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::log(
			"Parsing NodeCondExpr, Token Value: " + lex.peek().value + "\n");

	bool errorFlag = false;
	Node *condExpr = new NodeCondExpr();

	Node *logorExpr = NodeLogorExpr::parse(cs);
	if (logorExpr) {
		condExpr->addNode(logorExpr);
	} else {
		delete condExpr;
		return NULL;
	}

	if (lex.peek().value == "?") {
		condExpr->addNode(new TerminalNode(lex.read()));

		Node *expr = NodeExpr::parse(cs);
		if (expr) {
			condExpr->addNode(expr);
			if (lex.peek().value == ":") {
				condExpr->addNode(new TerminalNode(lex.read()));

				Node *nextCondExpr = NodeCondExpr::parse(cs);
				if (nextCondExpr) {
					condExpr->addNode(nextCondExpr);
				} else {
					errorFlag = true;
				}

			} else {
				cs.reportError();
				errorFlag = true;
			}

		} else {
			errorFlag = true;
		}
	}

	if (errorFlag) {
		delete condExpr;
		return NULL;
	}

	Logger::log(
			"Returning NodeCondExpr, Token Value: " + lex.peek().value + "\n");
	return condExpr;
}
