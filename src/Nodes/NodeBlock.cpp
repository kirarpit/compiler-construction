#include <AllNodeHeaders.h>

Node* NodeBlock::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logNodeEntry(__CLASS_NAME__, lex.peek());

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

	Logger::logNodeExit(__CLASS_NAME__, lex.peek());
	return block;
}

void NodeBlock::print(CompilerState &cs) {
	printST(cs);
	cs.os << '\n';
	for (unsigned int i = 0; i < children.size(); i++) {
		if (i) {
			children[i]->print(cs);
		}
	}
}

void NodeBlock::printST(CompilerState &cs) {
	myST->print(cs);
}

SymbolTable* NodeBlock::getST() {
	return myST;
}

void NodeBlock::walk(CompilerState &cs) {
	cs.lastBlock = this;
	for (unsigned int i = 0; i < children.size(); i++) {
		children[i]->walk(cs);
	}
	cs.lastBlock = cs.lastBlock->getST()->exitScope();
}
