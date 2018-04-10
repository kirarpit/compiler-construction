#include <AllNodeHeaders.h>

Node* NodeAsgnExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

	Node *asgnExpr = new NodeAsgnExpr();

	Node *condOrPostfixExpr = NodeCondExpr::parse(cs);
	if (condOrPostfixExpr) {
		asgnExpr->addNode(condOrPostfixExpr);

		if (lex.peek().value == TokenTable::TS[TN_equal]) {
			//check if it's indeed PE
			if (!condOrPostfixExpr->findPostfixExpr()) {
				Logger::log(
						"CE can't be PE, Token Value: " + lex.peek().stringify());

				cs.es.reportParseError(cs);
				delete asgnExpr;
				return NULL;
			}
			Logger::log("CE can be PE, Token Value: " + lex.peek().stringify());

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

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return asgnExpr;
}

void NodeAsgnExpr::walk(CompilerState &cs) {
	Logger::logWalkEntry(__CLASS_NAME__, this);

	walkAllChildren(cs);
	operatorWalk(cs);

	Logger::logWalkExit(__CLASS_NAME__, this);
}
