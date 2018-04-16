#include <AllNodeHeaders.h>

Node* NodeOptArraySpecs::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

	Node *arraySpecs = new NodeOptArraySpecs();

	if (lex.peek().value == TokenTable::TS[TN_opnbrk]) {
		Node *arraySpec = NodeArraySpec::parse(cs);
		if (arraySpec) {
			arraySpecs->addNode(arraySpec);

			Node *nextArraySpecs = NodeOptArraySpecs::parse(cs);
			if (nextArraySpecs) {
				arraySpecs->addNode(nextArraySpecs);
			} else {
				delete arraySpecs;
				return NULL;
			}
		} else {
			delete arraySpecs;
			return NULL;
		}
	}

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return arraySpecs;
}

void NodeOptArraySpecs::walk(CompilerState &cs) {
	Logger::logWalkEntry(__CLASS_NAME__, this);

	smartWalk(cs);

	Logger::logWalkExit(__CLASS_NAME__, this);
}
