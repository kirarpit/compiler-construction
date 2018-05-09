#include <AllNodeHeaders.h>

Node* NodeIOVar::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

	bool errorFlag = false;
	Node *ioVar = new NodeIOVar();

	if (lex.peek().type & TT_SHIFT_OP) {
		ioVar->addNode(new TerminalNode(lex.read()));

		if (lex.peek().type & TT_ID) {
			Node *postfixExpr = NodePostfixExpr::parse(cs);
			if (postfixExpr) {
				ioVar->addNode(postfixExpr);
			} else {
				errorFlag = true;
			}
		} else {
			errorFlag = true;
			cs.es.reportError(cs, "expecting an ID");
		}
	}

	if (errorFlag) {
		delete ioVar;
		ioVar = NULL;
	}

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return ioVar;
}

void NodeIOVar::walk(CompilerState &cs) {
	Logger::logWalkEntry(__CLASS_NAME__, this);

	walkAllChildren(cs);
	type = children[1]->getType();

	if (!type->isSigned() && !type->isUnsigned() && !type->isBool()) {
		cs.es.reportOpTypeError(cs, children[0]->getToken(), type, type,
				"invalid operands to binary expression ('lobocIO' and '%t2')");
	}

	if (!children[1]->isAssignable) {
		cs.es.reportTypeError(cs, children[0]->getToken(),
				children[1]->getType(), "expression is not assignable");
	}

	Logger::logWalkExit(__CLASS_NAME__, this);
}

void NodeIOVar::print(CompilerState &cs) {
	printFPIF(cs);
}

Register NodeIOVar::genCode(CompilerState &cs, CodeGenArgs cg) {
	Logger::logGenCodeEntry(__CLASS_NAME__, this);

	Register r1(-1);
	if (children.size() >= 2) {
		Register v0(0, RT_EVAL);
		Register a0(0, RT_ARG);

		cg.develop = GET_ADDRESS;
		r1 = children[1]->genCode(cs, cg);
		r1.offset = 0;

		if (children[0]->getToken().value == "<<") {
			cs.rf.printLIInst(cs, v0, 1);
			cs.rf.printInst(cs, "lw", a0, r1);

			cs.os << "\tsyscall\n";

		} else {
			cs.rf.printLIInst(cs, v0, 5);
			cs.os << "\tsyscall\n";

			cs.rf.printInst(cs, "sw", v0, r1);
		}
	} else {
		genCodeAll(cs, cg);
	}

	Logger::logGenCodeExit(__CLASS_NAME__, this);
	return r1;
}
