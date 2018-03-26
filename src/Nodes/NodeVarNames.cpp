#include <AllNodeHeaders.h>

Node* NodeVarNames::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

	Node *varNames = NULL;

	Node *varName = NodeVarName::parse(cs);
	if (varName) {
		varNames = new NodeVarNames();
		varNames->addNode(varName);

		Node *optVarNames = NodeOptVarNames::parse(cs);
		if (optVarNames) {
			varNames->addNode(optVarNames);
		} else {
			delete varNames;
			return NULL;
		}
	}

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return varNames;
}
