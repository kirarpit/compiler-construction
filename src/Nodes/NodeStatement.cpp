#include "Nodes/AllNodesHeader.h"

Node* NodeStatement::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::log(
			"Parsing NodeStatement, Token Value: " + lex.peek().value + "\n");

	bool errorFlag = false;
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
				errorFlag = true;
			}
		} else {
			errorFlag = true;
		}

	} else {
		Node *expr = NodeExpr::parse(cs);

		if (expr) {
			statement->addNode(expr);

			if (lex.peek().value == ";") {
				statement->addNode(new TerminalNode(lex.read()));
			} else {
				cs.reportError();
				errorFlag = true;
			}
		} else {
			errorFlag = true;
		}
	}

	if (errorFlag) {
		delete statement;
		return NULL;
	}

	Logger::log(
			"Returning NodeStatement, Token Value: " + lex.peek().value + "\n");
	return statement;
}
