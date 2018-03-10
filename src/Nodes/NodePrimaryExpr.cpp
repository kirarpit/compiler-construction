#include "Nodes/AllNodesHeader.h"

Node* NodePrimaryExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logNodeEntry("NodePrimaryExpr", lex.peek());

	bool errorFlag = false;
	Node *primaryExpr = new NodePrimaryExpr();

	if (lex.peek().type == TT_ID) {
		Token id = lex.read();
		primaryExpr->addNode(new TerminalNode(id));

		if (!cs.st->isDef)
			cs.st->insertVar(id);
	} else if (lex.peek().type == TT_NUM) {
		primaryExpr->addNode(new TerminalNode(lex.read()));
	} else if (lex.peek().value == TokenTable::TS[TN_opnpar]) {
		Logger::logConsTerm(lex.peek());
		lex.read();

		Node *expr = NodeExpr::parse(cs);
		if (expr) {
			primaryExpr->addNode(expr);

			if (lex.peek().value == TokenTable::TS[TN_clspar]) {
				Logger::logConsTerm(lex.peek());
				lex.read();
			} else {
				errorFlag = true;
				cs.es.reportError(cs);
			}
		} else {
			errorFlag = true;
		}
	} else {
		errorFlag = true;
		cs.es.reportError(cs);
	}

	if (errorFlag) {
		delete primaryExpr;
		return NULL;
	}

	Logger::logNodeExit("NodePrimaryExpr", lex.peek());
	return primaryExpr;
}
