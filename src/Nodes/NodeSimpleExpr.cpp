#include "Nodes/AllNodesHeader.h"

Node* NodeSimpleExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::log(
			"Parsing NodeSimpleExpr, Token Value: " + lex.peek().value);

	Node *simpleExpr = new NodeSimpleExpr();

	Node *term = NodeTerm::parse(cs);
	if (term) {
		simpleExpr->addNode(term);
	} else {
		delete simpleExpr;
		return NULL;
	}

	while (lex.peek().subType == "TERM_OP") {
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

	Logger::log(
			"Returning NodeSimpleExpr, Token Value: " + lex.peek().value
					+ "\n");
	return simpleExpr;
}
