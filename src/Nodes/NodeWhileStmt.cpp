#include <AllNodeHeaders.h>

Node* NodeWhileStmt::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logNodeEntry(__CLASS_NAME__, lex.peek());

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

	Logger::logNodeExit(__CLASS_NAME__, lex.peek());
	return whileStmt;
}
