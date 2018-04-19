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

	smartWalk(cs);

	Logger::logWalkExit(__CLASS_NAME__, this);
}

Register NodeExpr::genCode(CompilerState &cs, CodeGenArgs cg) {
	Logger::logGenCodeEntry(__CLASS_NAME__, this);

	Register r1(-1);
	if (children.size() == 1) {
		r1 = children[0]->genCode(cs);
	} else {
		r1 = children[0]->genCode(cs);
		r1 = children[2]->genCode(cs);
	}

	Logger::logGenCodeExit(__CLASS_NAME__, this);
	return r1;
}
