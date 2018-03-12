#include <AllNodeHeaders.h>

Node* NodeOptVarNames::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logNodeEntry(__CLASS_NAME__, lex.peek());

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

	Logger::logNodeExit(__CLASS_NAME__, lex.peek());
	return optVarNames;
}
