#include "Nodes/AllNodesHeader.h"

void NodeSpike3::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logNodeEntry(__CLASS_NAME__, lex.peek());

	Node *block = NodeBlock::parse(cs);
	if (block)
		block->print(cs);
	Logger::log("Deleting Block");
	delete block;

	if (cs.lexer.peek().type != TT_EOF) {
		cs.es.reportParseError(cs);
	}

	Logger::logConsTerm(lex.peek());
	lex.read();
}
