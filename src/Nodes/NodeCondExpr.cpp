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

		if (!children[0]->getType()->isBool()) {
			cs.es.reportTypeError(cs, children[0]->getToken(),
					children[0]->getType(),
					"value of type '%t' is not contextually convertible to 'bool'");
		}

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

	if (children.size() == 5) {
		if (children[2]->getType() != children[4]->getType()) {
			cs.es.reportOpTypeError(cs, children[1]->getToken(),
					children[2]->getType(), children[4]->getType(),
					"invalid operands to binary expression ('%t1' and '%t2')");
		} else
			type = children[2]->getType();
	}

	if (children.size() == 1) {
		if (children[0]->isAssignable)
			assignable();
	} else {
		if (children[2]->isAssignable && children[4]->isAssignable)
			assignable();
	}

	Logger::logWalkExit(__CLASS_NAME__, this);
}

Register NodeCondExpr::genCode(CompilerState &cs, CodeGenArgs cg) {
	Logger::logGenCodeEntry(__CLASS_NAME__, this);

	Register r1(-1);
	if (children.size() == 5) {

		int labelNo = cs.rf.getLabelNo();
		std::string fLabel = cs.rf.getLabel(FalseL, labelNo);
		std::string tLabel = cs.rf.getLabel(TrueL, labelNo);

		r1 = children[0]->genCode(cs, cg);
		cs.rf.printBranchInst(cs, "beq", r1, Register(0, RT_ZERO), fLabel);
		r1 = children[2]->genCode(cs, cg);
		cs.rf.printBranchInst(cs, "b", tLabel);

		cs.rf.printLabel(cs, fLabel);
		r1 = children[4]->genCode(cs, cg);

		cs.rf.printLabel(cs, tLabel);

	} else {
		genCodeAll(cs, cg);
	}

	Logger::logGenCodeExit(__CLASS_NAME__, this);
	return r1;
}

