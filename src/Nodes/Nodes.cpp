#include "Nodes/AllNodesHeader.h"

void NodeSpike3::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::log("Parsing NodeSpike3, Token Value: " + lex.peek().value + "\n");

	Node *block = NodeBlock::parse(cs);
	block->print(cs);
	delete block;

	Logger::log("Consumed Terminal:" + lex.peek().value + "\n");
	lex.read();
}
