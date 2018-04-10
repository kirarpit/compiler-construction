#include <AllNodeHeaders.h>

Node* NodeBlock::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

	SymbolTable *st = SymbolTable::enterScope(cs.lastBlock);
	Node *block = new NodeBlock(st);
	cs.lastBlock = block;

	Node *defs = NodeDefs::parse(cs);
	if (defs) {
		block->addNode(defs);

		st->isDef = false;
		Node *statements = NodeStatements::parse(cs);
		if (statements) {
			block->addNode(statements);
		} else {
			delete block;
			block = NULL;
		}
	} else {
		delete block;
		block = NULL;
	}

	cs.lastBlock = st->exitScope();

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return block;
}

void NodeBlock::print(CompilerState &cs) {
	printST(cs);
	cs.os << '\n';

	printAllChildren(cs);
}

void NodeBlock::printST(CompilerState &cs) {
	if (myST)
		myST->print(cs);
}

SymbolTable* NodeBlock::getST() {
	return myST;
}

void NodeBlock::walk(CompilerState &cs) {
	Logger::logWalkEntry(__CLASS_NAME__, this);

	cs.lastBlock = this;
	walkAllChildren(cs);
	cs.lastBlock = cs.lastBlock->getST()->exitScope();

	Logger::logWalkExit(__CLASS_NAME__, this);
}
