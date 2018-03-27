#include <AllNodeHeaders.h>

Node* NodeWhileStmt::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

	Node *whileStmt = new NodeWhileStmt();

	if (lex.peek().value == TokenTable::TS[TN_while]) {
		whileStmt->addNode(new TerminalNode(lex.read()));

		if (lex.peek().value == TokenTable::TS[TN_opnpar]) {
			whileStmt->addNode(new TerminalNode(lex.read()));

			Node *expr = NodeExpr::parse(cs);
			if (expr) {
				whileStmt->addNode(expr);

				if (lex.peek().value == TokenTable::TS[TN_clspar]) {
					whileStmt->addNode(new TerminalNode(lex.read()));

					Node *statement = NodeStatement::parse(cs);
					if (statement) {
						whileStmt->addNode(statement);
					}
				} else {
					cs.es.reportParseError(cs);
				}
			}
		} else {
			cs.es.reportParseError(cs);
		}
	} else {
		cs.es.reportParseError(cs);
	}

	if (cs.es.error) {
		delete whileStmt;
		whileStmt = NULL;
	}

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return whileStmt;
}

void NodeWhileStmt::walk(CompilerState &cs) {
	Logger::logWalkEntry(__CLASS_NAME__, this);

	this->NonTerminalNode::walk(cs);

	if (children.size() == 5) {
		if (children[2]->isConstant) {
			Logger::log(__CLASS_NAME__ + ", Starting constant folding");

			if (children[2]->getToken().value == "0") {
				deleteChildren();
			}
		}
	}

	Logger::logWalkExit(__CLASS_NAME__, this);
}

void NodeWhileStmt::print(CompilerState &cs) {
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
