#include<NodeArraySpec.h>
#include<NodeArraySize.h>

Node* NodeArraySpec::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logNodeEntry(__CLASS_NAME__, lex.peek());

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
		cs.es.reportParseError(cs);
		delete arraySpec;
		return NULL;
	}

	Logger::logNodeExit(__CLASS_NAME__, lex.peek());
	return arraySpec;
}
