#include "Nodes/AllNodesHeader.h"

Node* NodeVarDef::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::log("Parsing NodeVarDef, Token Value: " + lex.peek().value);

	Node *varDef = NULL;

	Node *typeSpec = NodeTypeSpec::parse(cs);
	if (typeSpec) {
		varDef = new NodeVarDef();
		varDef->addNode(typeSpec);

		Node *varNames = NodeVarNames::parse(cs);
		if (varNames) {
			varDef->addNode(varNames);

			if (lex.peek().value == TokenTable::TnInfo[TN_semi]) {
				varDef->addNode(new TerminalNode(lex.read()));

				cs.st->flush(false);
			} else {
				cs.reportError();
				delete varDef;
			}
		} else {
			delete varDef;
		}
	}

	if (cs.error) {
		cs.recover();
		cs.st->flush(true);
		varDef = new NodeVarDef();
	}

	Logger::log("Returning NodeVarDef, Token Value: " + lex.peek().value);
	return varDef;
}
