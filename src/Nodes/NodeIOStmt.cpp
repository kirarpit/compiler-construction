#include <AllNodeHeaders.h>

Node* NodeIOStmt::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

	bool errorFlag = false;
	Node *ioStmt = new NodeIOStmt();

	if (lex.peek().value == TokenTable::TS[TN_loboc]) {
		ioStmt->addNode(new TerminalNode(lex.read()));

		if (lex.peek().type & TT_SHIFT_OP) {
			ioStmt->addNode(new TerminalNode(lex.read()));

			if (lex.peek().type == TT_ID) {
				Token id = lex.read();
				ioStmt->addNode(new TerminalNode(id));

				if (!cs.lastBlock->getST()->insertOrUpdateVar(cs, id)) {
					errorFlag = true;

				} else {
					if (lex.peek().value == TokenTable::TS[TN_semi]) {
						ioStmt->addNode(new TerminalNode(lex.read()));
					} else
						cs.es.reportError(cs, "expecting ';'");
				}

			} else {
				errorFlag = true;
				cs.es.reportError(cs, "expecting an ID");
			}
		} else {
			errorFlag = true;
			cs.es.reportError(cs, "expecting a SHIFT_OP literal");
		}
	}

	if (cs.es.error) {
		delete ioStmt;
		ioStmt = NULL;

		cs.es.recover(cs);
		if (lex.peek().value == TokenTable::TS[TN_semi]) {
			Logger::logTerminal(lex.peek());
			lex.read();
			ioStmt = new NodeIOStmt();
		} else {
			if (errorFlag)
				cs.es.reportError(cs, "expecting ';'");
		}
	}

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return ioStmt;
}

void NodeIOStmt::walk(CompilerState &cs) {
	Logger::logWalkEntry(__CLASS_NAME__, this);

	smartWalk(cs);
	if (children.size() == 4) {
		type = children[2]->getType();
	}

	Logger::logWalkExit(__CLASS_NAME__, this);
}

void NodeIOStmt::print(CompilerState &cs) {
	cs.os.printWhiteSpaces();

	type->shortPrint(cs);
	cs.os << '(';
	for (unsigned int i = 0; i < children.size() - 1; i++) {
		children[i]->print(cs);
	}
	cs.os << ')';
	children[children.size() - 1]->print(cs);
}

Register NodeIOStmt::genCode(CompilerState &cs, CodeGenArgs cg) {
	Logger::logGenCodeEntry(__CLASS_NAME__, this);

	Register r1(-1);
	if (children.size() == 4) {
		Register v0(0, RT_EVAL);
		Register a0(0, RT_ARG);

		cg.develop = GET_ADDRESS;
		r1 = children[2]->genCode(cs, cg);
		r1.offset = 0;

		if (children[1]->getToken().value == "<<") {
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
