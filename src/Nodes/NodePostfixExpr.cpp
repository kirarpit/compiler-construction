#include <AllNodeHeaders.h>

Node* NodePostfixExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logNodeEntry(__CLASS_NAME__, lex.peek());

	Node *postfixExpr = new NodePostfixExpr();

	Node *primaryExpr = NodePrimaryExpr::parse(cs);
	if (primaryExpr) {
		postfixExpr->addNode(primaryExpr);
	} else {
		delete postfixExpr;
		return NULL;
	}

	while (1) {
		if (lex.peek().type & TT_POSTUN_OP) {
			Node *tempPostfixExpr = new NodePostfixExpr();

			tempPostfixExpr->addNode(postfixExpr);
			tempPostfixExpr->addNode(new TerminalNode(lex.read()));

			postfixExpr = tempPostfixExpr;
		} else if (lex.peek().value == TokenTable::TS[TN_opnbrk]) {
			Node *arraySpec = NodeArraySpec::parse(cs);

			if (arraySpec) {
				Node *tempPostfixExpr = new NodePostfixExpr();

				tempPostfixExpr->addNode(postfixExpr);
				tempPostfixExpr->addNode(arraySpec);

				postfixExpr = tempPostfixExpr;
			} else {
				delete postfixExpr;
				return NULL;
			}
		} else {
			break;
		}
	}

	Logger::logNodeExit(__CLASS_NAME__, lex.peek());
	return postfixExpr;
}
