#include "Nodes/AllNodesHeader.h"

Node* NodeEqExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logNodeEntry(__CLASS_NAME__, lex.peek());

	Node *eqExpr = new NodeEqExpr();

	Node *relExpr = NodeRelExpr::parse(cs);
	if (relExpr) {
		eqExpr->addNode(relExpr);
	} else {
		delete eqExpr;
		return NULL;
	}

	while (lex.peek().type & TT_EQ_OP) {
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

	Logger::logNodeExit(__CLASS_NAME__, lex.peek());
	return eqExpr;
}
