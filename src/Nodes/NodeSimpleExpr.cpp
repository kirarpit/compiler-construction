#include "Nodes/AllNodesHeader.h"

Node* NodeSimpleExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logNodeEntry("NodeSimpleExpr", lex.peek());

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

	Logger::logNodeExit("NodeSimpleExpr", lex.peek());
	return simpleExpr;
}
