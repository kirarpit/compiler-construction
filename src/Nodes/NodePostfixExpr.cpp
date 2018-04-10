#include <AllNodeHeaders.h>

Node* NodePostfixExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

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

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return postfixExpr;
}

void NodePostfixExpr::walk(CompilerState &cs) {
	Logger::logWalkEntry(__CLASS_NAME__, this);

	smartWalk(cs);

	if (children.size() == 2) {
		if (children[1]->isTerminal) {
			if (children[0]->getType()->isSigned()
					|| children[0]->getType()->isUnsigned()
					|| children[0]->getType()->isPointer()) {
				type = children[0]->getType();
			} else {
				//error
				exit(1);
			}
		} else {
			if (children[1]->getSize() == 2)
				type = children[0]->getType()->deref(TP_POINTER);
			else
				type = children[0]->getType()->deref(TP_ARRAY);
		}
	}

	Logger::logWalkExit(__CLASS_NAME__, this);
}
