#include "Nodes/AllNodesHeader.h"

Node* NodeStatement::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::log("Parsing NodeStatement, Token Value: " + lex.peek().value);

	Node *statement = new NodeStatement();

	if (lex.peek().value == "{") {
		statement->addNode(new TerminalNode(lex.read()));

		Node *statements = NodeStatements::parse(cs);
		if (statements) {
			statement->addNode(statements);

			if (lex.peek().value == "}") {
				statement->addNode(new TerminalNode(lex.read()));
			} else {
				cs.reportError();
			}
		}
	} else {
		Node *expr = NodeExpr::parse(cs);

		if (expr) {
			statement->addNode(expr);

			if (lex.peek().value == ";") {
				statement->addNode(new TerminalNode(lex.read()));
			} else {
				cs.reportError();
			}
		}
	}

	if (cs.error) {
		delete statement;
		statement = new NodeStatement();
		cs.recover();
		cs.st->flush(true);
	}

	Logger::log("Returning NodeStatement, Token Value: " + lex.peek().value);
	return statement;
}
