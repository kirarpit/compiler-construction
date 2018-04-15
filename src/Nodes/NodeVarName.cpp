#include <AllNodeHeaders.h>

Node* NodeVarName::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

	Node *varName = NULL;

	if (lex.peek().type == TT_ID) {
		varName = new NodeVarName();
		Token id = lex.read();
		varName->addNode(new TerminalNode(id));

		if (!cs.lastBlock->getST()->insertOrUpdateVar(cs, id)) {
			delete varName;
			varName = NULL;
		}
	} else {
		cs.es.reportError(cs, "expecting ID");
	}

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return varName;
}

void NodeVarName::walk(CompilerState &cs) {
	Logger::logWalkEntry(__CLASS_NAME__, this);

	walkAllChildren(cs);

	Logger::logWalkExit(__CLASS_NAME__, this);
}

void NodeVarName::genCode(CompilerState &cs) {
	Logger::logGenCodeEntry(__CLASS_NAME__, this);

	Logger::logGenCodeExit(__CLASS_NAME__, this);
}
