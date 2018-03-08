#include "Nodes/AllNodesHeader.h"

Node* NodeBlock::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::log("Parsing NodeBlock, Token Value: " + lex.peek().value + "\n");

	if (!cs.st) {
		cs.st = new SymbolTable();
	} else {
		cs.st = cs.st->enterScope();
	}

	st = cs.st;
	Node *block = NULL;

	Node *defs = NodeDefs::parse(cs);
	if (defs) {
		block = new NodeBlock();
		block->addNode(defs);

		cs.st->isDef = false;
		Node *statements = NodeStatements::parse(cs);
		if (statements) {
			block->addNode(statements);
		} else {
			delete block;
			block = NULL;
		}
	}

	cs.st = cs.st->exitScope();

	Logger::log("Returning NodeBlock, Token Value: " + lex.peek().value + "\n");
	return block;
}
