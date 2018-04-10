#include <AllNodeHeaders.h>

Node* NodeEqExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

	Node *eqExpr = new NodeEqExpr();

	Node *relExpr = NodeRelExpr::parse(cs);
	if (relExpr) {
		eqExpr->addNode(relExpr);
	} else {
		delete eqExpr;
		return NULL;
	}

	while (lex.peek().type & TT_EQ_OP) {
		Node *tempEqExpr = new NodeEqExpr();

		tempEqExpr->addNode(eqExpr);
		tempEqExpr->addNode(new TerminalNode(lex.read()));
		Node *relExpr = NodeRelExpr::parse(cs);
		if (relExpr) {
			tempEqExpr->addNode(relExpr);
		} else {
			delete tempEqExpr;
			return NULL;
		}

		eqExpr = tempEqExpr;
	}

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return eqExpr;
}

void NodeEqExpr::walk(CompilerState &cs) {
	Logger::logWalkEntry(__CLASS_NAME__, this);

	smartWalk(cs);

	Logger::logWalkExit(__CLASS_NAME__, this);
}
