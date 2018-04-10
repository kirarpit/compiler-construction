#include <AllNodeHeaders.h>

Node* NodeDef::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

	Node *def = NULL;

	Node *varDef = NodeVarDef::parse(cs);
	if (varDef) {
		def = new NodeDef();
		def->addNode(varDef);
	}

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return def;
}

void NodeDef::walk(CompilerState &cs) {
	Logger::logWalkEntry(__CLASS_NAME__, this);

	walkAllChildren(cs);

	Logger::logWalkExit(__CLASS_NAME__, this);
}
