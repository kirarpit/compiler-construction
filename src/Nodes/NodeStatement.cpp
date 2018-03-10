#include "Nodes/AllNodesHeader.h"

Node* NodeStatement::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logNodeEntry("NodeStatement", lex.peek());

	Node *statement = new NodeStatement();

	if (lex.peek().value == TokenTable::TS[TN_opnbrc]) {
		statement->addNode(new TerminalNode(lex.read()));

		Node *statements = NodeStatements::parse(cs);
		if (statements) {
			statement->addNode(statements);

			if (lex.peek().value == TokenTable::TS[TN_clsbrc]) {
				statement->addNode(new TerminalNode(lex.read()));
			} else {
				cs.es.reportError(cs);
			}
		}
	} else {
		Node *expr = NodeExpr::parse(cs);

		if (expr) {
			statement->addNode(expr);

			if (lex.peek().value == TokenTable::TS[TN_semi]) {
				statement->addNode(new TerminalNode(lex.read()));
			} else {
				cs.es.reportError(cs);
			}
		}
	}

	if (cs.es.error) {
		delete statement;
		statement = new NodeStatement();
		cs.es.recover(cs);
		cs.st->flush(true);
	}

	Logger::logNodeExit("NodeStatement", lex.peek());

	return statement;
}
