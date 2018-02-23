#include "Nodes/AllNodesHeader.h"

Node* NodeArraySpec::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::log(
			"Parsing NodeArraySpec, Token Value: " + lex.peek().value + "\n");

	bool errorFlag = false;
	Node *arraySpec = new NodeArraySpec();

	if (lex.peek().value == "[") {
		arraySpec->addNode(new TerminalNode(lex.read()));

		Node *arraySize = NodeArraySize::parse(cs);
		if (arraySize) {
			arraySpec->addNode(arraySize);
		} else {
			delete arraySpec;
			return NULL;
		}

		if (lex.peek().value == "]") {
			arraySpec->addNode(new TerminalNode(lex.read()));
		} else {
			errorFlag = true;
		}

	} else {
		errorFlag = true;
	}

	if (errorFlag) {
		cs.reportError();
		delete arraySpec;
		return NULL;
	}

	Logger::log(
			"Returning NodeArraySpec, Token Value: " + lex.peek().value + "\n");
	return arraySpec;
}