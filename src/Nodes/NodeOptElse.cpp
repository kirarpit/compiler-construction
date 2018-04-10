#include <AllNodeHeaders.h>

Node* NodeOptElse::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

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

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return optElse;
}

void NodeOptElse::walk(CompilerState &cs) {
	Logger::logWalkEntry(__CLASS_NAME__, this);

	walkAllChildren(cs);

	Logger::logWalkExit(__CLASS_NAME__, this);
}

void NodeOptElse::print(CompilerState &cs) {
	cs.os.printWhiteSpaces();
	for (unsigned int i = 0; i < children.size(); i++) {
		if (i == 1) {
			cs.os << "\n";
			cs.os.indent();
		}
		children[i]->print(cs);

		if (i == 1) {
			cs.os.deindent();
		}
	}
}
