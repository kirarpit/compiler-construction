#include "Nodes/AllNodesHeader.h"

Node* NodeDef::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::log("Parsing NodeDef, Token Value: " + lex.peek().value + "\n");

	Node *def = NULL;

	Node *varDef = NodeVarDef::parse(cs);
	if (varDef) {
		def = new NodeDef();
		def->addNode(varDef);
	}

	Logger::log("Returning NodeDef, Token Value: " + lex.peek().value + "\n");
	return def;
}
