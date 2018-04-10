#include <AllNodeHeaders.h>

Node* NodeStatement::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

	Node *statement = new NodeStatement();

	if (lex.peek().value == TokenTable::TS[TN_opnbrc]) {
		statement->addNode(new TerminalNode(lex.read()));

		Node *block = NodeBlock::parse(cs);
		if (block) {
			statement->addNode(block);

			if (lex.peek().value == TokenTable::TS[TN_clsbrc]) {
				statement->addNode(new TerminalNode(lex.read()));
			} else {
				cs.es.reportParseError(cs);
			}
		}

	} else if (lex.peek().value == TokenTable::TS[TN_if]) {
		Node *ifStmt = NodeIfStmt::parse(cs);
		if (ifStmt) {
			statement->addNode(ifStmt);
		}

	} else if (lex.peek().value == TokenTable::TS[TN_while]) {
		Node *whileStmt = NodeWhileStmt::parse(cs);
		if (whileStmt) {
			statement->addNode(whileStmt);
		}

	} else {
		Node *expr = NodeExpr::parse(cs);

		if (expr) {
			statement->addNode(expr);

			if (lex.peek().value == TokenTable::TS[TN_semi]) {
				statement->addNode(new TerminalNode(lex.read()));
			} else {
				cs.es.reportParseError(cs);
			}
		}
	}

	if (cs.es.error) {
		delete statement;
		statement = new NodeStatement();
		cs.es.recover(cs);
	}

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return statement;
}

void NodeStatement::walk(CompilerState &cs) {
	Logger::logWalkEntry(__CLASS_NAME__, this);

	walkAllChildren(cs);

	Logger::logWalkExit(__CLASS_NAME__, this);
}

void NodeStatement::print(CompilerState &cs) {
	if (children.size() == 1) { //if or while statements
		children[0]->print(cs);
		return;
	}
	cs.os.printWhiteSpaces();

	if (children.size() == 2 && children[1]->getToken().value == ";") { //expression
		printAllChildren(cs);
		cs.os << '\n';
		return;
	}

	for (unsigned int i = 0; i < children.size(); i++) { //block
		if (i == children.size() - 1) {
			cs.os.deindent();
			cs.os.printWhiteSpaces();
		}

		children[i]->print(cs);

		if (i == 0) {
			cs.os << "\n";
			cs.os.indent();
		}

		if (i == children.size() - 1)
			cs.os << '\n';
	}
}
