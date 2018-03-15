#include <AllNodeHeaders.h>

Node* NodeOptElse::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logNodeEntry(__CLASS_NAME__, lex.peek());

	Node *optElse = new NodeOptElse();
	if (lex.peek().value == TokenTable::TS[TN_else]) {
		optElse->addNode(new TerminalNode(lex.read()));

		Node *statement = NodeStatement::parse(cs);
		if (statement) {
			optElse->addNode(statement);
		} else {
			delete optElse;
			optElse = NULL;
		}
	}

	Logger::logNodeExit(__CLASS_NAME__, lex.peek());
	return optElse;
}
