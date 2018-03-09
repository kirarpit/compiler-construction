#include "Nodes/AllNodesHeader.h"

Node* NodeEqExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::log("Parsing NodeEqExpr, Token Value: " + lex.peek().value);

	Node *eqExpr = new NodeEqExpr();

	Node *relExpr = NodeRelExpr::parse(cs);
	if (relExpr) {
		eqExpr->addNode(relExpr);
	} else {
		delete eqExpr;
		return NULL;
	}

	while (lex.peek().subType == "EQ_OP") {
		Node *tempEqExpr = new NodeEqExpr();

		tempEqExpr->addNode(eqExpr);
		tempEqExpr->addNode(new TerminalNode(lex.read()));
		Node *relExpr = NodeRelExpr::parse(cs);
		if (relExpr) {
			tempEqExpr->addNode(relExpr);
		} else {
			delete tempEqExpr;
			return NULL;
		}

		eqExpr = tempEqExpr;
	}

	Logger::log(
			"Returning NodeEqExpr, Token Value: " + lex.peek().value);
	return eqExpr;
}
