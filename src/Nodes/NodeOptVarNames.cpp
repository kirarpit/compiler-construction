#include <AllNodeHeaders.h>

Node* NodeOptVarNames::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

	Node *optVarNames = new NodeOptVarNames();

	if (lex.peek().value == TokenTable::TS[TN_comma]) {
		optVarNames->addNode(new TerminalNode(lex.read()));

		Node *varNames = NodeVarNames::parse(cs);
		if (varNames) {
			optVarNames->addNode(varNames);
		} else {
			delete optVarNames;
			return NULL;
		}
	}

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return optVarNames;
}

void NodeOptVarNames::walk(CompilerState &cs) {
	Logger::logWalkEntry(__CLASS_NAME__, this);

	walkAllChildren(cs);

	Logger::logWalkExit(__CLASS_NAME__, this);
}
