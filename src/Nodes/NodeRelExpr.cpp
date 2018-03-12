#include <AllNodeHeaders.h>

Node* NodeRelExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logNodeEntry(__CLASS_NAME__, lex.peek());

	Node *relExpr = new NodeRelExpr();

	Node *simpleExpr = NodeSimpleExpr::parse(cs);
	if (simpleExpr) {
		relExpr->addNode(simpleExpr);
	} else {
		delete relExpr;
		return NULL;
	}

	while (lex.peek().type & TT_REL_OP) {
		Node *tempRelExpr = new NodeRelExpr();

		tempRelExpr->addNode(relExpr);
		tempRelExpr->addNode(new TerminalNode(lex.read()));
		Node *simpleExpr = NodeSimpleExpr::parse(cs);
		if (simpleExpr) {
			tempRelExpr->addNode(simpleExpr);
		} else {
			delete tempRelExpr;
			return NULL;
		}

		relExpr = tempRelExpr;
	}

	Logger::logNodeExit(__CLASS_NAME__, lex.peek());
	return relExpr;
}
