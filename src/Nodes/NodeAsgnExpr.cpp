#include "Nodes/AllNodesHeader.h"

Node* NodeAsgnExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::log(
			"Parsing NodeAsgnExpr, Token Value: " + lex.peek().value);

	Node *asgnExpr = new NodeAsgnExpr();

	Node *condOrPostfixExpr = NodeCondExpr::parse(cs);
	if (condOrPostfixExpr) {
		asgnExpr->addNode(condOrPostfixExpr);

		if (1 && lex.peek().value == "=") {
			//check if it's indeed PE
			Logger::log(
					"Checking if CE could be PE, Token Value: "
							+ lex.peek().value);
			if (!condOrPostfixExpr->findPostfixExpr()) {
				Logger::log(
						"CE can't be PE, Token Value: " + lex.peek().value
								+ "\n");

				cs.reportError();
				delete asgnExpr;
				return NULL;
			}
			Logger::log(
					"CE could be PE, Token Value: " + lex.peek().value);

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

	Logger::log(
			"Returning NodeAsgnExpr, Token Value: " + lex.peek().value);
	return asgnExpr;
}
