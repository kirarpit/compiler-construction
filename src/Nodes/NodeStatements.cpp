#include <AllNodeHeaders.h>

Node* NodeStatements::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

	Node *statements = new NodeStatements();

	if (lex.peek().type != TT_EOF
			&& lex.peek().value != TokenTable::TS[TN_clsbrc]) {
		Node *statement = NodeStatement::parse(cs);
		if (statement) {
			statements->addNode(statement);

			Node *nextStatements = NodeStatements::parse(cs);
			if (nextStatements) {
				statements->addNode(nextStatements);
			} else {
				delete statements;
				statements = NULL;
			}
		} else {
			delete statements;
			statements = NULL;
		}
	}

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return statements;
}

void NodeStatements::walk(CompilerState &cs) {
	Logger::logWalkEntry(__CLASS_NAME__, this);

	walkAllChildren(cs);

	Logger::logWalkExit(__CLASS_NAME__, this);
}

void NodeStatements::genCode(CompilerState &cs) {
	Logger::logGenCodeEntry(__CLASS_NAME__, this);

	Logger::logGenCodeExit(__CLASS_NAME__, this);
}
