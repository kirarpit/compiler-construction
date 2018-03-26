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
	} else {
		cs.es.reportParseError(cs);
	}

	if (cs.es.error) {
		delete ifStmt;
		ifStmt = NULL;
	}

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return ifStmt;
}

void NodeIfStmt::print(CompilerState &cs) {
	for (unsigned int i = 0; i < children.size(); i++) {
		if (i == 1)
			cs.os << " ";
		if (i == 4) {
			cs.os << "\n";
			cs.os.indent();
		}
		if (i == 5)
			cs.os.deindent();
		children[i]->print(cs);
	}
}
