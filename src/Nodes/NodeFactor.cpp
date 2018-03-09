#include "Nodes/AllNodesHeader.h"

Node* NodeFactor::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::log("Parsing NodeFactor, Token Value: " + lex.peek().value);

	Node *factor = new NodeFactor();

	if (lex.peek().subType == "PREUN_OP" || lex.peek().subType == "POSTUN_OP"
			|| lex.peek().value == "-") {
		factor->addNode(new TerminalNode(lex.read()));
		Node *nextFactor = NodeFactor::parse(cs);
		if (nextFactor) {
			factor->addNode(nextFactor);
		} else {
			delete factor;
			return NULL;
		}
	} else {
		Node *postfixExpr = NodePostfixExpr::parse(cs);
		if (postfixExpr) {
			factor->addNode(postfixExpr);
		} else {
			delete factor;
			return NULL;
		}
	}

	Logger::log(
			"Returning NodeFactor, Token Value: " + lex.peek().value);
	return factor;
}
