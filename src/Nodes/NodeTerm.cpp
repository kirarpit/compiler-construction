#include <AllNodeHeaders.h>

Node* NodeTerm::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

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

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return term;
}

void NodeTerm::walk(CompilerState &cs) {
	Logger::logWalkEntry(__CLASS_NAME__, this);

	smartWalk(cs);

	Logger::logWalkExit(__CLASS_NAME__, this);
}
