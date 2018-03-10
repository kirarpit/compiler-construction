#include "Nodes/AllNodesHeader.h"

Node* NodeTerm::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logNodeEntry(__CLASS_NAME__, lex.peek());

	Node *term = new NodeTerm();

	Node *factor = NodeFactor::parse(cs);
	if (factor) {
		term->addNode(factor);
	} else {
		delete term;
		return NULL;
	}

	while (lex.peek().type & TT_FACTOR_OP) {
		Node *tempTerm = new NodeTerm();

		tempTerm->addNode(term);
		tempTerm->addNode(new TerminalNode(lex.read()));
		Node *factor = NodeFactor::parse(cs);
		if (factor) {
			tempTerm->addNode(factor);
		} else {
			delete tempTerm;
			return NULL;
		}

		term = tempTerm;
	}

	Logger::logNodeExit(__CLASS_NAME__, lex.peek());
	return term;
}
