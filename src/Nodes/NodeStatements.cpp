#include "Nodes/AllNodesHeader.h"

Node* NodeStatements::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::log(
			"Parsing NodeStatements, Token Value: " + lex.peek().value);

	Node *statements = new NodeStatements();

	if (lex.peek().type != "EOF" && lex.peek().value != "}") {
		Node *statement = NodeStatement::parse(cs);
		if (statement) {
			statements->addNode(statement);

			Node *nextStatements = NodeStatements::parse(cs);
			if (nextStatements) {
				statements->addNode(nextStatements);
			} else {
				delete statements;
				return NULL;
			}
		} else {
			delete statements;
			return NULL;
		}
	}

	Logger::log(
			"Returning NodeStatements, Token Value: " + lex.peek().value
					+ "\n");
	return statements;
}
