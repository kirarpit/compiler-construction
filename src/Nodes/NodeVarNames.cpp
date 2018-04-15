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
			varNames->addNode(new NodeOptVarNames());
			cs.es.recover(cs);
		}
	}

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return varNames;
}

void NodeVarNames::walk(CompilerState &cs) {
	Logger::logWalkEntry(__CLASS_NAME__, this);

	walkAllChildren(cs);

	Logger::logWalkExit(__CLASS_NAME__, this);
}

void NodeVarNames::genCode(CompilerState &cs) {
	Logger::logGenCodeEntry(__CLASS_NAME__, this);

	Logger::logGenCodeExit(__CLASS_NAME__, this);
}
