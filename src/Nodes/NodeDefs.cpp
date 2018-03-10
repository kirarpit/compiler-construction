#include "Nodes/AllNodesHeader.h"

Node* NodeDefs::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::log("Parsing NodeDefs, Token Value: " + lex.peek().value);

	Node *defs = new NodeDefs();

	if (lex.peek().value == TokenTable::TnInfo[TN_bool]
			|| lex.peek().value == TokenTable::TnInfo[TN_unsigned]
			|| lex.peek().value == TokenTable::TnInfo[TN_signed]) {
		Node *def = NodeDef::parse(cs);
		if (def) {
			defs->addNode(def);

			Node *nextDefs = NodeDefs::parse(cs);
			if (nextDefs) {
				defs->addNode(nextDefs);
			} else {
				delete defs;
				return NULL;
			}
		} else {
			delete defs;
			return NULL;
		}
	}

	Logger::log("Returning NodeDefs, Token Value: " + lex.peek().value);
	return defs;
}
