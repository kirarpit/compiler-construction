#include <AllNodeHeaders.h>

Node* NodePrimaryExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

	bool errorFlag = false;
	Node *primaryExpr = new NodePrimaryExpr();

	if (lex.peek().type == TT_ID) {
		Token id = lex.read();
		primaryExpr->addNode(new TerminalNode(id));
		primaryExpr->assignable();

		if (!cs.lastBlock->getST()->isDef) {
			if (!cs.lastBlock->getST()->insertOrUpdateVar(cs, id)) {
				errorFlag = true;
			}
		}

	} else if (lex.peek().type == TT_NUM) {
		primaryExpr->addNode(new TerminalNode(lex.read()));

	} else if (lex.peek().value == TokenTable::TS[TN_opnpar]) {
		Logger::logTerminal(lex.peek());
		lex.read();

		Node *expr = NodeExpr::parse(cs);
		if (expr) {
			primaryExpr->addNode(expr);
			if (expr->isAssignable)
				primaryExpr->assignable();

			if (lex.peek().value == TokenTable::TS[TN_clspar]) {
				Logger::logTerminal(lex.peek());
				lex.read();
			} else {
				errorFlag = true;
				cs.es.reportError(cs, "expecting ')'");
			}
		} else {
			errorFlag = true;
		}
	} else {
		errorFlag = true;
		cs.es.reportError(cs, "expecting ID or a Num");
	}

	if (errorFlag) {
		delete primaryExpr;
		return NULL;
	}

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return primaryExpr;
}

void NodePrimaryExpr::walk(CompilerState &cs) {
	Logger::logWalkEntry(__CLASS_NAME__, this);

	smartWalk(cs);

	Logger::logWalkExit(__CLASS_NAME__, this);
}

Register NodePrimaryExpr::genCode(CompilerState &cs, CodeGenArgs cg) {
	Logger::logGenCodeEntry(__CLASS_NAME__, this);

	Logger::logGenCodeExit(__CLASS_NAME__, this);
	return children[0]->genCode(cs, cg);
}
