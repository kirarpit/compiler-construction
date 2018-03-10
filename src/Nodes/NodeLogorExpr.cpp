#include "Nodes/AllNodesHeader.h"

Node* NodeLogorExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::log(
			"Parsing NodeLogorExpr, Token Value: " + lex.peek().value);

	Node *logorExpr = new NodeLogorExpr();

	Node *logandExpr = NodeLogandExpr::parse(cs);
	if (logandExpr) {
		logorExpr->addNode(logandExpr);
	} else {
		delete logorExpr;
		return NULL;
	}

	while (lex.peek().value == TokenTable::TS[TN_oror]) {
		Node *tempLogorExpr = new NodeLogorExpr();

		tempLogorExpr->addNode(logorExpr);
		tempLogorExpr->addNode(new TerminalNode(lex.read()));
		Node *logandExpr = NodeLogandExpr::parse(cs);
		if (logandExpr) {
			tempLogorExpr->addNode(logandExpr);
		} else {
			delete tempLogorExpr;
			return NULL;
		}

		logorExpr = tempLogorExpr;
	}

	Logger::log(
			"Returning NodeLogorExpr, Token Value: " + lex.peek().value);
	return logorExpr;
}
