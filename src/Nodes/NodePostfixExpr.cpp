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
			Type *tp = children[0]->getType();
			if (tp->isSigned() || tp->isUnsigned() || tp->isPointer()) {
				type = tp;
			} else {
				cs.es.reportTypeError(cs, children[1]->getToken(), tp,
						"cannot post increment/decrement value of type '%t'");
			}
		} else {
			if (children[1]->getSize() == 2)
				type = children[0]->getType()->deref(cs,
						children[1]->getChild(0)->getToken(), TP_POINTER);
			else
				type = children[0]->getType()->deref(cs,
						children[1]->getChild(0)->getToken(), TP_ARRAY);
		}
	}

	Logger::logWalkExit(__CLASS_NAME__, this);
}

void NodePostfixExpr::genCode(CompilerState &cs) {
	Logger::logGenCodeEntry(__CLASS_NAME__, this);

	Logger::logGenCodeExit(__CLASS_NAME__, this);
}
