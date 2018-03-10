#include "Nodes/AllNodesHeader.h"

Node* NodeDef::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logNodeEntry("NodeDef", lex.peek());

	Node *def = NULL;

	Node *varDef = NodeVarDef::parse(cs);
	if (varDef) {
		def = new NodeDef();
		def->addNode(varDef);
	}

	Logger::logNodeExit("NodeDef", lex.peek());
	return def;
}
