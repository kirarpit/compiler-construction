#include "Nodes/AllNodesHeader.h"

void NodeSpike3::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::log("Parsing NodeSpike3, Token Value: " + lex.peek().value);

	Node *block = NodeBlock::parse(cs);
	if (block)
		block->print(cs);
	Logger::log("Deleting BLock");
	delete block;

	Logger::log("Consumed Terminal:" + lex.peek().value);
	lex.read();
}
