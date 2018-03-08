#include "Nodes/AllNodesHeader.h"

Node* NodeVarDef::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::log("Parsing NodeVarDef, Token Value: " + lex.peek().value + "\n");

	bool errorRecovery = false;
	Node *varDef = NULL;

	Node *typeSpec = NodeTypeSpec::parse(cs);
	if (typeSpec) {
		varDef = new NodeVarDef();
		varDef->addNode(typeSpec);

		Node *varNames = NodeVarNames::parse(cs);
		if (varNames) {
			varDef->addNode(varNames);

			if (lex.peek().value == ";") {
				varDef->addNode(new TerminalNode(lex.read()));

				cs.st->flush();
			} else {
				cs.reportError();
				delete varDef;
				errorRecovery = true;
			}
		} else {
			delete varDef;
			errorRecovery = true;
		}
	}

	if (errorRecovery) {
		cs.recover();
		varDef = new NodeVarDef();
	}

	Logger::log(
			"Returning NodeVarDef, Token Value: " + lex.peek().value + "\n");
	return varDef;
}
