#include<Lexer.h>
#include<CompilerState.h>
#include<Logger.h>
#include<NodeBlock.h>
#include<ErrorStream.h>
#include<NodeSpike5.h>

void NodeSpike5::compile(CompilerState &cs) {
	Lexer &lex = cs.lexer;

	Node *block = NodeBlock::parse(cs);
	if (block) {
		block->walk(cs);
		cs.os << "\t.text\n";
		cs.os << "\t.align 4\n";
		cs.os << "\t.globl main\n";
		cs.os << "main:\n";

		block->genCode(cs);

		cs.os << "\tjr $ra\n";

//		cs.os << "\n";
//		block->print(cs);
		delete block;
	} else {
		cs.es.recover(cs);
		if (lex.peek().type != TT_EOF) {
			cs.es.reportError(cs, "expecting EOF");
		} else {
			Logger::logTerminal(lex.peek());
			lex.read();
		}
	}
}
