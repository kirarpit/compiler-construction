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

		if (!cs.es.getErrorCount()) {
			cs.rf.printTextInst(cs, ".data");
			cs.rf.printLabel(cs, "newline");
			cs.rf.printTextInst(cs, ".asciiz \"\\n\"");

			cs.rf.printTextInst(cs, ".text");
			cs.rf.printTextInst(cs, ".align 4");
			cs.rf.printTextInst(cs, ".globl main");
			cs.rf.printLabel(cs, "main");

			block->genCode(cs, CodeGenArgs());

			cs.rf.printTextInst(cs, "jr $ra");
		} else {
			block->print(cs);
		}

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
