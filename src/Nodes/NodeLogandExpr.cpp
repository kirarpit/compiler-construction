#include <AllNodeHeaders.h>

Node* NodeLogandExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

	Node *logandExpr = new NodeLogandExpr();

	Node *eqExpr = NodeEqExpr::parse(cs);
	if (eqExpr) {
		logandExpr->addNode(eqExpr);
	} else {
		delete logandExpr;
		return NULL;
	}

	while (lex.peek().value == TokenTable::TS[TN_andand]) {
		Node *tempLogandExpr = new NodeLogandExpr();

		tempLogandExpr->addNode(logandExpr);
		tempLogandExpr->addNode(new TerminalNode(lex.read()));
		Node *eqExpr = NodeEqExpr::parse(cs);
		if (eqExpr) {
			tempLogandExpr->addNode(eqExpr);
		} else {
			delete tempLogandExpr;
			return NULL;
		}

		logandExpr = tempLogandExpr;
	}

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return logandExpr;
}

void NodeLogandExpr::walk(CompilerState &cs) {
	Logger::logWalkEntry(__CLASS_NAME__, this);

	this->NonTerminalNode::walk(cs);
	operatorWalk(cs);

	Logger::logWalkExit(__CLASS_NAME__, this);
}
