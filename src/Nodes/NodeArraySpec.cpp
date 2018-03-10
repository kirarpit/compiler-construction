#include "Nodes/AllNodesHeader.h"

Node* NodeArraySpec::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logNodeEntry("NodeArraySpec", lex.peek());

	bool errorFlag = false;
	Node *arraySpec = new NodeArraySpec();

	if (lex.peek().value == TokenTable::TS[TN_opnbrk]) {
		arraySpec->addNode(new TerminalNode(lex.read()));

		Node *arraySize = NodeArraySize::parse(cs);
		if (arraySize) {
			arraySpec->addNode(arraySize);
		} else {
			delete arraySpec;
			return NULL;
		}

		if (lex.peek().value == TokenTable::TS[TN_clsbrk]) {
			arraySpec->addNode(new TerminalNode(lex.read()));
		} else {
			errorFlag = true;
		}
	} else {
		errorFlag = true;
	}

	if (errorFlag) {
		cs.es.reportError();
		delete arraySpec;
		return NULL;
	}

	Logger::logNodeExit("NodeArraySpec", lex.peek());
	return arraySpec;
}
