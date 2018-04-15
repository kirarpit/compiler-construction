#include<NodeArraySpec.h>
#include <NodeOptArraySize.h>

Node* NodeArraySpec::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

	bool errorFlag = false;
	std::string em;
	Node *arraySpec = new NodeArraySpec();

	if (lex.peek().value == TokenTable::TS[TN_opnbrk]) {
		arraySpec->addNode(new TerminalNode(lex.read()));

		Node *arraySize = NodeOptArraySize::parse(cs);
		if (arraySize) {
			arraySpec->addNode(arraySize);
		} else {
			delete arraySpec;
			return NULL;
		}

		if (lex.peek().value == TokenTable::TS[TN_clsbrk]) {
			arraySpec->addNode(new TerminalNode(lex.read()));

			if (cs.lastBlock->getST()->isDef) {
				arraySpec->walk(cs);

				Logger::log("Array Spec size: %d", arraySpec->getSize());
				if (arraySpec->getSize() == 3
						&& arraySpec->getChild(1)->isConstant) {
					cs.lastBlock->getST()->updateVarType(cs, TP_ARRAY,
							arraySpec->getChild(1)->getToken().getIntVal());
				} else if (arraySpec->getSize() == 2) {
					cs.lastBlock->getST()->updateVarType(cs, TP_POINTER);
				} else {
					em = "variable length arrays are not supported";
					errorFlag = true;
				}
			}
		} else {
			errorFlag = true;
			em = "expecting ']'";
		}
	} else {
		errorFlag = true;
		em = "expecting '['";
	}

	if (errorFlag) {
		cs.es.reportError(cs, em);
		delete arraySpec;
		return NULL;
	}

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return arraySpec;
}

void NodeArraySpec::walk(CompilerState &cs) {
	Logger::logWalkEntry(__CLASS_NAME__, this);

	walkAllChildren(cs);

	Logger::logWalkExit(__CLASS_NAME__, this);
}

void NodeArraySpec::genCode(CompilerState &cs) {
	Logger::logGenCodeEntry(__CLASS_NAME__, this);

	Logger::logGenCodeExit(__CLASS_NAME__, this);
}
