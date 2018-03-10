#include "Nodes/AllNodesHeader.h"

Node* NodeBlock::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logNodeEntry(__CLASS_NAME__, lex.peek());

	if (!cs.st) {
		cs.st = new SymbolTable();
	} else {
		cs.st = cs.st->enterScope();
	}

	Node *block = NULL;

	Node *defs = NodeDefs::parse(cs);
	if (defs) {
		block = new NodeBlock(cs.st);
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

	Logger::logNodeExit(__CLASS_NAME__, lex.peek());
	return block;
}
