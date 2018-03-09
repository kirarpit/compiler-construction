#include "Nodes/AllNodesHeader.h"

Node* NodeOptVarNames::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::log(
			"Parsing NodeOptVarNames, Token Value: " + lex.peek().value);

	Node *optVarNames = new NodeOptVarNames();

	if (lex.peek().value == ",") {
		optVarNames->addNode(new TerminalNode(lex.read()));

		Node *varNames = NodeVarNames::parse(cs);
		if (varNames) {
			optVarNames->addNode(varNames);
		} else {
			delete optVarNames;
			return NULL;
		}
	}

	Logger::log(
			"Returning NodeOptVarNames, Token Value: " + lex.peek().value
					+ "\n");
	return optVarNames;
}
