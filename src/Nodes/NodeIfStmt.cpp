#include <AllNodeHeaders.h>

Node* NodeIfStmt::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

	Node *ifStmt = new NodeIfStmt();

	if (lex.peek().value == TokenTable::TS[TN_if]) {
		ifStmt->addNode(new TerminalNode(lex.read()));

		if (lex.peek().value == TokenTable::TS[TN_opnpar]) {
			ifStmt->addNode(new TerminalNode(lex.read()));

			Node *expr = NodeExpr::parse(cs);
			if (expr) {
				ifStmt->addNode(expr);

				if (lex.peek().value == TokenTable::TS[TN_clspar]) {
					ifStmt->addNode(new TerminalNode(lex.read()));

					Node *statement = NodeStatement::parse(cs);
					if (statement) {
						ifStmt->addNode(statement);

						Node *optElse = NodeOptElse::parse(cs);
						if (optElse) {
							ifStmt->addNode(optElse);
						}
					}
				} else {
					cs.es.reportParseError(cs);
				}
			}
		} else {
			cs.es.reportParseError(cs);
		}
	}

	if (cs.es.error) {
		delete ifStmt;
		ifStmt = NULL;
	}

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return ifStmt;
}

void NodeIfStmt::walk(CompilerState &cs) {
	Logger::logWalkEntry(__CLASS_NAME__, this);

	children[2]->walk(cs);
	Node *temp = reduceBranch(children[2]);
	if (temp)
		children[2] = temp;

	if (children[2]->isConstant) {
		Logger::log(__CLASS_NAME__ + ", constant folding");

		int index = -1;

		Node *temp = NULL;
		if (children[2]->getToken().value == "0") {
			if (children.size() == 6 && children[5]->getSize() == 2) {
				children[5]->deleteChild(0);
				temp = children[5];
				index = 5;
			}
		} else {
			temp = children[4];
			index = 4;
		}

		if (index != -1)
			clearChild(index);

		deleteChildren();
		if (temp)
			addNode(temp);

	}
	walkAllChildren(cs);

	Logger::logWalkExit(__CLASS_NAME__, this);
}

void NodeIfStmt::print(CompilerState &cs) {
	cs.os.printWhiteSpaces();
	for (unsigned int i = 0; i < children.size(); i++) {
		if (i == 1)
			cs.os << " ";
		if (i == 4) {
			cs.os << "\n";
			cs.os.indent();
		}

		children[i]->print(cs);

		if (i == 4) {
			cs.os.deindent();
		}
	}
}
