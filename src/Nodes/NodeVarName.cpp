#include "Nodes/AllNodesHeader.h"

Node* NodeVarName::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logNodeEntry("NodeVarName", lex.peek());

	Node *varName = NULL;

	if (lex.peek().type == TT_ID) {
		varName = new NodeVarName();
		Token id = lex.read();
		varName->addNode(new TerminalNode(id));

		cs.st->insertVar(id);
	} else {
		cs.reportError();
	}

	Logger::logNodeExit("NodeVarName", lex.peek());
	return varName;
}
