#include <AllNodeHeaders.h>

Node* NodeArraySpecs::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logNodeEntry(__CLASS_NAME__, lex.peek());

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

	Logger::logNodeExit(__CLASS_NAME__, lex.peek());
	return arraySpecs;
}
