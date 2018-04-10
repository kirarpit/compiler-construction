#include <AllNodeHeaders.h>

Node* NodeExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

	Node *expr = new NodeExpr();

	Node *asgnExpr = NodeAsgnExpr::parse(cs);
	if (asgnExpr) {
		expr->addNode(asgnExpr);
	} else {
		delete expr;
		return NULL;
	}

	while (lex.peek().value == TokenTable::TS[TN_comma]) {
		Node *tempExpr = new NodeExpr();

		tempExpr->addNode(expr);
		tempExpr->addNode(new TerminalNode(lex.read()));
		Node *asgnExpr = NodeAsgnExpr::parse(cs);
		if (asgnExpr) {
			tempExpr->addNode(asgnExpr);
		} else {
			delete tempExpr;
			return NULL;
		}

		expr = tempExpr;
	}

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return expr;
}

void NodeExpr::walk(CompilerState &cs) {
	Logger::logWalkEntry(__CLASS_NAME__, this);

	walkAllChildren(cs);
	operatorWalk(cs);

	Logger::logWalkExit(__CLASS_NAME__, this);
}
