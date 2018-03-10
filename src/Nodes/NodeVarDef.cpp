#include "Nodes/AllNodesHeader.h"

Node* NodeVarDef::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logNodeEntry(__CLASS_NAME__, lex.peek());

	Node *varDef = NULL;

	Node *typeSpec = NodeTypeSpec::parse(cs);
	if (typeSpec) {
		varDef = new NodeVarDef();
		varDef->addNode(typeSpec);

		Node *varNames = NodeVarNames::parse(cs);
		if (varNames) {
			varDef->addNode(varNames);

			if (lex.peek().value == TokenTable::TS[TN_semi]) {
				varDef->addNode(new TerminalNode(lex.read()));

				cs.st->flush(false);
			} else {
				cs.es.reportParseError(cs);
				delete varDef;
			}
		} else {
			delete varDef;
		}
	}

	if (cs.es.error) {
		cs.es.recover(cs);
		cs.st->flush(true);
		varDef = new NodeVarDef();
	}

	Logger::logNodeExit(__CLASS_NAME__, lex.peek());
	return varDef;
}
