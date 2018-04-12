#include <AllNodeHeaders.h>

Node* NodeVarName::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

	Node *varName = NULL;

	if (lex.peek().type == TT_ID) {
		varName = new NodeVarName();
		Token id = lex.read();
		varName->addNode(new TerminalNode(id));

		cs.lastBlock->getST()->insertOrUpdateVar(cs, id);
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
