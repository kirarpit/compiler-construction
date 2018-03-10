#include "Nodes/AllNodesHeader.h"

Node* NodeRelExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::log("Parsing NodeRelExpr, Token Value: " + lex.peek().value);

	Node *relExpr = new NodeRelExpr();

	Node *simpleExpr = NodeSimpleExpr::parse(cs);
	if (simpleExpr) {
		relExpr->addNode(simpleExpr);
	} else {
		delete relExpr;
		return NULL;
	}

	while (lex.peek().type & TT_REL_OP) {
		Node *tempRelExpr = new NodeRelExpr();

		tempRelExpr->addNode(relExpr);
		tempRelExpr->addNode(new TerminalNode(lex.read()));
		Node *simpleExpr = NodeSimpleExpr::parse(cs);
		if (simpleExpr) {
			tempRelExpr->addNode(simpleExpr);
		} else {
			delete tempRelExpr;
			return NULL;
		}

		relExpr = tempRelExpr;
	}

	Logger::log("Returning NodeRelExpr, Token Value: " + lex.peek().value);
	return relExpr;
}
