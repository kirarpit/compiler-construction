#include "Nodes/AllNodesHeader.h"

Node* NodeLogandExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::log("Parsing NodeLogandExpr, Token Value: " + lex.peek().value);

	Node *logandExpr = new NodeLogandExpr();

	Node *eqExpr = NodeEqExpr::parse(cs);
	if (eqExpr) {
		logandExpr->addNode(eqExpr);
	} else {
		delete logandExpr;
		return NULL;
	}

	while (lex.peek().value == "&&") {
		Node *tempLogandExpr = new NodeLogandExpr();

		tempLogandExpr->addNode(logandExpr);
		tempLogandExpr->addNode(new TerminalNode(lex.read()));
		Node *eqExpr = NodeEqExpr::parse(cs);
		if (eqExpr) {
			tempLogandExpr->addNode(eqExpr);
		} else {
			delete tempLogandExpr;
			return NULL;
		}

		logandExpr = tempLogandExpr;
	}

	Logger::log("Returning NodeLogandExpr, Token Value: " + lex.peek().value);
	return logandExpr;
}
