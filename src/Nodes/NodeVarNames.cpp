#include "Nodes/AllNodesHeader.h"

Node* NodeVarNames::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::log("Parsing NodeVarNames, Token Value: " + lex.peek().value);

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

	Logger::log("Returning NodeVarNames, Token Value: " + lex.peek().value);
	return varNames;
}
