#include "Nodes/AllNodesHeader.h"

Node* NodeArraySpecs::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::log(
			"Parsing NodeArraySpec, Token Value: " + lex.peek().value + "\n");

	Node *arraySpecs = new NodeArraySpecs();

	if (lex.peek().value == "[") {
		Node *arraySpec = NodeArraySpec::parse(cs);
		if (arraySpec) {
			arraySpecs->addNode(arraySpec);

			int name;
			cs.output.startBuffer();
			arraySpec->print(cs);
			string arraySpecString = cs.output.clearBuffer();
			if (arraySpecString == "") {
				name = POINTER;
			} else {
				name = ARRAY;
			}
			cs.st->updateType(name, arraySpecString);

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

	Logger::log(
			"Returning NodeArraySpec, Token Value: " + lex.peek().value + "\n");
	return arraySpecs;
}
