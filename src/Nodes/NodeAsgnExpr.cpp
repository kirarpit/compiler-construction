#include "Nodes/AllNodesHeader.h"

Node* NodeAsgnExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logNodeEntry("NodeAsgnExpr", lex.peek());

	Node *asgnExpr = new NodeAsgnExpr();

	Node *condOrPostfixExpr = NodeCondExpr::parse(cs);
	if (condOrPostfixExpr) {
		asgnExpr->addNode(condOrPostfixExpr);

		if (lex.peek().value == TokenTable::TS[TN_equal]) {
			//check if it's indeed PE
			if (!condOrPostfixExpr->findPostfixExpr()) {
				Logger::log(
						"CE can't be PE, Token Value: " + lex.peek().print());

				cs.es.reportError();
				delete asgnExpr;
				return NULL;
			}
			Logger::log("CE can be PE, Token Value: " + lex.peek().print());

			asgnExpr->addNode(new TerminalNode(lex.read()));

			Node *nextAsgnExpr = NodeAsgnExpr::parse(cs);
			if (nextAsgnExpr) {
				asgnExpr->addNode(nextAsgnExpr);
			} else {
				delete asgnExpr;
				return NULL;
			}
		}
	} else {
		delete asgnExpr;
		return NULL;
	}

	Logger::logNodeExit("NodeAsgnExpr", lex.peek());
	return asgnExpr;
}
