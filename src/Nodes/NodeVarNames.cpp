#include "Nodes/AllNodesHeader.h"

Node* NodeVarNames::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logNodeEntry("NodeVarNames", lex.peek());

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

	Logger::logNodeExit("NodeVarNames", lex.peek());
	return varNames;
}
