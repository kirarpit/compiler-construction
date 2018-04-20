#include <AllNodeHeaders.h>

Node* NodeAsgnExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

	Node *asgnExpr = new NodeAsgnExpr();

	Node *condOrPostfixExpr = NodeCondExpr::parse(cs);
	if (condOrPostfixExpr) {
		asgnExpr->addNode(condOrPostfixExpr);

		if (lex.peek().value == TokenTable::TS[TN_equal]) {
			if (!condOrPostfixExpr->findPostfixExpr()) {
				cs.es.reportError(cs, "invalid assignment left-hand side");
				delete asgnExpr;
				return NULL;
			}

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

	smartWalk(cs);

	if (children.size() == 3) {
		if (!children[0]->isAssignable) {
			cs.es.reportTypeError(cs, children[1]->getToken(),
					children[2]->getType(), "expression is not assignable");
		}
	}

	Logger::logWalkExit(__CLASS_NAME__, this);
}

Register NodeAsgnExpr::genCode(CompilerState &cs, CodeGenArgs cg) {
	Logger::logGenCodeEntry(__CLASS_NAME__, this);

	Register r1(-1);
	if (children.size() == 3) {
		cg.develop = GET_ADDRESS;
		r1 = children[0]->genCode(cs, cg);
		cs.rf.storeTemp(cs, r1);

		cg.develop = GET_VALUE;
		r1 = children[2]->genCode(cs, cg);
		Register r2 = cs.rf.loadTemp(cs);

		r2.offset = 0;
		if (type->getAlignment() == 4)
			cs.rf.printInst(cs, "sw", r1, r2);
		else
			cs.rf.printInst(cs, "sb", r1, r2);
	} else {
		genCodeAll(cs, cg);
	}

	Logger::logGenCodeExit(__CLASS_NAME__, this);
	return r1;
}
