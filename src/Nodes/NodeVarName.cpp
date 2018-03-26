#include <AllNodeHeaders.h>

Node* NodeVarName::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

	Node *varName = NULL;

	if (lex.peek().type == TT_ID) {
		varName = new NodeVarName();
		Token id = lex.read();
		varName->addNode(new TerminalNode(id));

		cs.lastBlock->getST()->insertVar(id);
	} else {
		cs.es.reportParseError(cs);
	}

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return varName;
}
