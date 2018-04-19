#include <AllNodeHeaders.h>

Node* NodeRelExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

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

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return relExpr;
}

void NodeRelExpr::walk(CompilerState &cs) {
	Logger::logWalkEntry(__CLASS_NAME__, this);

	smartWalk(cs);

	Logger::logWalkExit(__CLASS_NAME__, this);
}

Register NodeRelExpr::genCode(CompilerState &cs, CodeGenArgs cg) {
	Logger::logGenCodeEntry(__CLASS_NAME__, this);

	Register r1 = genCodeArithmetic(cs);

	Logger::logGenCodeExit(__CLASS_NAME__, this);
	return r1;
}
