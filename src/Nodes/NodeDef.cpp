#include "Nodes/AllNodesHeader.h"

Node* NodeDef::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logNodeEntry(__CLASS_NAME__, lex.peek());

	Node *def = NULL;

	Node *varDef = NodeVarDef::parse(cs);
	if (varDef) {
		def = new NodeDef();
		def->addNode(varDef);
	}

	Logger::logNodeExit(__CLASS_NAME__, lex.peek());
	return def;
}
