#include <AllNodeHeaders.h>

Node* NodeCondExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

	bool errorFlag = false;
	Node *condExpr = new NodeCondExpr();

	Node *logorExpr = NodeLogorExpr::parse(cs);
	if (logorExpr) {
		condExpr->addNode(logorExpr);
	} else {
		delete condExpr;
		return NULL;
	}

	if (lex.peek().value == TokenTable::TS[TN_quest]) {
		condExpr->addNode(new TerminalNode(lex.read()));

		Node *expr = NodeExpr::parse(cs);
		if (expr) {
			condExpr->addNode(expr);
			if (lex.peek().value == TokenTable::TS[TN_colon]) {
				condExpr->addNode(new TerminalNode(lex.read()));

				Node *nextCondExpr = NodeCondExpr::parse(cs);
				if (nextCondExpr) {
					condExpr->addNode(nextCondExpr);
				} else {
					errorFlag = true;
				}

			} else {
				cs.es.reportError(cs, "expecting ':'");
				errorFlag = true;
			}

		} else {
			errorFlag = true;
		}
	}

	if (errorFlag) {
		delete condExpr;
		return NULL;
	}

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return condExpr;
}

void NodeCondExpr::walk(CompilerState &cs) {
	Logger::logWalkEntry(__CLASS_NAME__, this);

	if (children.size() == 5) {
		children[0]->walk(cs);
		Node *temp = reduceBranch(children[0]);
		if (temp)
			children[0] = temp;

		if (children[0]->isConstant) {
			Node *temp = NULL;
			int index = -1;

			if (children[0]->getToken().value == "1") {
				temp = children[2];
				index = 2;

			} else {
				temp = children[4];
				index = 4;
			}

			clearChild(index);
			deleteChildren();
			addNode(temp);
		}
	}
	smartWalk(cs);

	Logger::logWalkExit(__CLASS_NAME__, this);
}

void NodeCondExpr::genCode(CompilerState &cs) {
	Logger::logGenCodeEntry(__CLASS_NAME__, this);

	Logger::logGenCodeExit(__CLASS_NAME__, this);
}
