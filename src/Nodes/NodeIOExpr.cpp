#include <AllNodeHeaders.h>

Node* NodeIOExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

	bool errorFlag = false;
	Node *ioExpr = new NodeIOExpr();

	if (lex.peek().value == TokenTable::TS[TN_loboc]) {
		ioExpr->addNode(new TerminalNode(lex.read()));

		if (lex.peek().type & TT_SHIFT_OP) {
			Node *ioVar = NodeIOVar::parse(cs);
			if (ioVar) {
				ioExpr->addNode(ioVar);

				Node *optIOExpr = NodeOptIOExpr::parse(cs);
				if (optIOExpr) {
					ioExpr->addNode(optIOExpr);
				} else {
					errorFlag = true;
				}
			} else {
				errorFlag = true;
			}
		} else {
			errorFlag = true;
			cs.es.reportError(cs, "expecting a Shift Operator");
		}
	}

	if (errorFlag) {
		delete ioExpr;
		ioExpr = NULL;
	}

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return ioExpr;
}

void NodeIOExpr::walk(CompilerState &cs) {
	Logger::logWalkEntry(__CLASS_NAME__, this);

	walkAllChildren(cs);
	type = children[1]->getType();

	Logger::logWalkExit(__CLASS_NAME__, this);
}

void NodeIOExpr::print(CompilerState &cs) {
	printFPIF(cs);
}

Register NodeIOExpr::genCode(CompilerState &cs, CodeGenArgs cg) {
	Logger::logGenCodeEntry(__CLASS_NAME__, this);

	Register r1(-1);
	genCodeAll(cs, cg);

	Logger::logGenCodeExit(__CLASS_NAME__, this);
	return r1;
}
