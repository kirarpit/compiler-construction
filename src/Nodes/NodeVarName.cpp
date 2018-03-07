#include "Nodes/AllNodesHeader.h"

Node* NodeVarName::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::log("Parsing NodeVarName, Token Value: " + lex.peek().value + "\n");

	Node *varName = NULL;

	if (lex.peek().type == "Identifier") {
		varName = new NodeVarName();
		Token id = lex.read();
		varName->addNode(new TerminalNode(id));

		cs.st->insertVar(id);
	} else {
		cs.reportError();
	}

	Logger::log(
			"Returning NodeVarName, Token Value: " + lex.peek().value + "\n");
	return varName;
}
