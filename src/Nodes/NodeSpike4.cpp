#include<NodeSpike4.h>
#include<Lexer.h>
#include<CompilerState.h>
#include<Logger.h>
#include<NodeBlock.h>
#include<ErrorStream.h>

void NodeSpike4::compile(CompilerState &cs) {
	Lexer &lex = cs.lexer;

	Node *block = NodeBlock::parse(cs);
	if (block) {
		block->walk(cs);
		block->print(cs);
		delete block;
	}

	if (lex.peek().type != TT_EOF) {
		cs.es.reportParseError(cs);
	}
}
