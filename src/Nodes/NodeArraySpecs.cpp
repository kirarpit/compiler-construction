#include "Nodes/AllNodesHeader.h"

Node* NodeArraySpecs::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logNodeEntry("NodeArraySpec", lex.peek());

	Node *arraySpecs = new NodeArraySpecs();

	if (lex.peek().value == TokenTable::TS[TN_opnbrk]) {
		Node *arraySpec = NodeArraySpec::parse(cs);
		if (arraySpec) {
			arraySpecs->addNode(arraySpec);

			cs.st->updateVarType(ARRAY, arraySpec);

			Node *nextArraySpecs = NodeArraySpecs::parse(cs);
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

	Logger::logNodeExit("NodeArraySpec", lex.peek());
	return arraySpecs;
}
