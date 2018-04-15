#include <AllNodeHeaders.h>

Node* NodeDefs::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

	Node *defs = new NodeDefs();

	if (lex.peek().value == TokenTable::TS[TN_bool]
			|| lex.peek().value == TokenTable::TS[TN_unsigned]
			|| lex.peek().value == TokenTable::TS[TN_signed]) {
		Node *def = NodeDef::parse(cs);
		if (def) {
			defs->addNode(def);

			Node *nextDefs = NodeDefs::parse(cs);
			if (nextDefs) {
				defs->addNode(nextDefs);
			} else {
				delete defs;
				defs = NULL;
			}
		} else {
			delete defs;
			defs = NULL;
		}
	}

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return defs;
}

void NodeDefs::walk(CompilerState &cs) {
	Logger::logWalkEntry(__CLASS_NAME__, this);

	walkAllChildren(cs);

	Logger::logWalkExit(__CLASS_NAME__, this);
}

void NodeDefs::genCode(CompilerState &cs) {
	Logger::logGenCodeEntry(__CLASS_NAME__, this);

	Logger::logGenCodeExit(__CLASS_NAME__, this);
}
