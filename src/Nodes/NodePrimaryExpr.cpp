#include "Nodes/AllNodesHeader.h"

Node* NodePrimaryExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::log(
			"Parsing NodePrimaryExpr, Token Value: " + lex.peek().value);

	bool errorFlag = false;
	Node *primaryExpr = new NodePrimaryExpr();

	if (lex.peek().type == "Identifier") {
		Token id = lex.read();
		primaryExpr->addNode(new TerminalNode(id));

		if (!cs.st->isDef)
			cs.st->insertVar(id);
	} else if (lex.peek().type == "Number") {
		primaryExpr->addNode(new TerminalNode(lex.read()));
	} else if (lex.peek().value == "(") {
		Logger::log("Consumed Terminal:" + lex.peek().value);
		lex.read();

		Node *expr = NodeExpr::parse(cs);
		if (expr) {
			primaryExpr->addNode(expr);

			if (lex.peek().value == ")") {
				Logger::log("Consumed Terminal:" + lex.peek().value);
				lex.read();
			} else {
				errorFlag = true;
				cs.reportError();
			}
		} else {
			errorFlag = true;
		}
	} else {
		errorFlag = true;
		cs.reportError();
	}

	if (errorFlag) {
		delete primaryExpr;
		return NULL;
	}

	Logger::log(
			"Returning NodePrimaryExpr, Token Value: " + lex.peek().value);
	return primaryExpr;
}
