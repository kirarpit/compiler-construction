#include "Nodes/AllNodesHeader.h"

Node* NodeStatements::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logNodeEntry(__CLASS_NAME__, lex.peek());

	Node *statements = new NodeStatements();

	if (lex.peek().type != TT_EOF && lex.peek().value != TokenTable::TS[TN_clsbrc]) {
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

	Logger::logNodeExit(__CLASS_NAME__, lex.peek());
	return statements;
}
