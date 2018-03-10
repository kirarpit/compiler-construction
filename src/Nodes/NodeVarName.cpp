#include "Nodes/AllNodesHeader.h"

Node* NodeVarName::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logNodeEntry(__CLASS_NAME__, lex.peek());

	Node *varName = NULL;

	if (lex.peek().type == TT_ID) {
		varName = new NodeVarName();
		Token id = lex.read();
		varName->addNode(new TerminalNode(id));

		cs.st->insertVar(id);
	} else {
		cs.es.reportParseError(cs);
	}

	Logger::logNodeExit(__CLASS_NAME__, lex.peek());
	return varName;
}
