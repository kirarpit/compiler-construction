#include <AllNodeHeaders.h>

Node* NodeSimpleExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

	Node *simpleExpr = new NodeSimpleExpr();

	Node *term = NodeTerm::parse(cs);
	if (term) {
		simpleExpr->addNode(term);
	} else {
		delete simpleExpr;
		return NULL;
	}

	while (lex.peek().type & TT_TERM_OP) {
		Node *tempSimpleExpr = new NodeSimpleExpr();

		tempSimpleExpr->addNode(simpleExpr);
		tempSimpleExpr->addNode(new TerminalNode(lex.read()));
		Node *term = NodeTerm::parse(cs);
		if (term) {
			tempSimpleExpr->addNode(term);
		} else {
			delete tempSimpleExpr;
			return NULL;
		}

		simpleExpr = tempSimpleExpr;
	}

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return simpleExpr;
}

void NodeSimpleExpr::walk(CompilerState &cs) {
	Logger::logWalkEntry(__CLASS_NAME__, this);

	smartWalk(cs);

	Logger::logWalkExit(__CLASS_NAME__, this);
}

Register NodeSimpleExpr::genCode(CompilerState &cs) {
	Logger::logGenCodeEntry(__CLASS_NAME__, this);

	Register r1 = genCodeArithmetic(cs);

	Logger::logGenCodeExit(__CLASS_NAME__, this);
	return r1;
}
