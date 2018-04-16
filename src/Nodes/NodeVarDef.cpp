#include <AllNodeHeaders.h>

Node* NodeVarDef::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

	bool error = false;
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
			} else
				cs.es.reportError(cs, "expecting ';'");
		} else
			error = true;
	} else
		error = true;

	if (cs.es.error) {
		delete varDef;
		varDef = NULL;

		cs.es.recover(cs);
		if (lex.peek().value == TokenTable::TS[TN_semi]) {
            Logger::logTerminal(lex.peek());
			lex.read();
			varDef = new NodeVarDef();
		} else {
			if (error)
				cs.es.reportError(cs, "expecting ';'");
		}
	}

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return varDef;
}

void NodeVarDef::walk(CompilerState &cs) {
	Logger::logWalkEntry(__CLASS_NAME__, this);

	walkAllChildren(cs);

	Logger::logWalkExit(__CLASS_NAME__, this);
}
