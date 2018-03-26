#include<NodeArraySpec.h>
#include <NodeOptArraySize.h>

Node* NodeArraySpec::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logNodeEntry(__CLASS_NAME__, lex.peek());

	bool errorFlag = false;
	Node *arraySpec = new NodeArraySpec();

	if (lex.peek().value == TokenTable::TS[TN_opnbrk]) {
		arraySpec->addNode(new TerminalNode(lex.read()));

		Node *arraySize = NodeOptArraySize::parse(cs);
		if (arraySize) {
			arraySpec->addNode(arraySize);

			if (cs.lastBlock->getST()->isDef) {
				arraySpec->walk(cs);

				if (arraySpec->getSize() == 3
						&& arraySpec->getChild(1)->isConstant) {
					cs.lastBlock->getST()->updateVarType(TP_ARRAY,
							stoi(arraySpec->getChild(1)->getToken().value));
				} else if (arraySpec->getSize() == 2) {
					cs.lastBlock->getST()->updateVarType(TP_POINTER, 0);
				} else {
					//error
					std::cout << "array spec size must be a constant during declaration";
				}
			}
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
