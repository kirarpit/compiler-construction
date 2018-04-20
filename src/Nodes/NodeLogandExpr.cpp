#include <AllNodeHeaders.h>

Node* NodeLogandExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

	Node *logandExpr = new NodeLogandExpr();

	Node *eqExpr = NodeEqExpr::parse(cs);
	if (eqExpr) {
		logandExpr->addNode(eqExpr);
	} else {
		delete logandExpr;
		return NULL;
	}

	while (lex.peek().value == TokenTable::TS[TN_andand]) {
		Node *tempLogandExpr = new NodeLogandExpr();

		tempLogandExpr->addNode(logandExpr);
		tempLogandExpr->addNode(new TerminalNode(lex.read()));
		Node *eqExpr = NodeEqExpr::parse(cs);
		if (eqExpr) {
			tempLogandExpr->addNode(eqExpr);
		} else {
			delete tempLogandExpr;
			return NULL;
		}

		logandExpr = tempLogandExpr;
	}

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return logandExpr;
}

void NodeLogandExpr::walk(CompilerState &cs) {
	Logger::logWalkEntry(__CLASS_NAME__, this);

	smartWalk(cs);

	Logger::logWalkExit(__CLASS_NAME__, this);
}

Register NodeLogandExpr::genCode(CompilerState &cs, CodeGenArgs cg) {
	Logger::logGenCodeEntry(__CLASS_NAME__, this);

	Register r1(-1);
	if (children.size() == 3) {
		cg.fall = FALL_TRUE;
		cg.l1 = FalseL;
		cg.l2 = TrueL;

		r1 = genFallThroughCode(cs, cg);
	} else {
		genCodeAll(cs, cg);
	}

	Logger::logGenCodeExit(__CLASS_NAME__, this);
	return r1;
}
