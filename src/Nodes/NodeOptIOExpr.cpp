#include <AllNodeHeaders.h>

Node* NodeOptIOExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

	bool errorFlag = false;
	Node *optIOExpr = new NodeOptIOExpr();

	if (lex.peek().type & TT_SHIFT_OP) {
		Node *ioVar = NodeIOVar::parse(cs);
		if (ioVar) {
			optIOExpr->addNode(ioVar);

			Node *nextOptIOExpr = NodeOptIOExpr::parse(cs);
			if (nextOptIOExpr) {
				optIOExpr->addNode(nextOptIOExpr);
			} else {
				errorFlag = true;
			}
		} else {
			errorFlag = true;
		}
	}

	if (errorFlag) {
		delete optIOExpr;
		optIOExpr = NULL;
	}

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return optIOExpr;
}

void NodeOptIOExpr::walk(CompilerState &cs) {
	Logger::logWalkEntry(__CLASS_NAME__, this);

	walkAllChildren(cs);
	if (children.size())
		type = children[0]->getType();

	Logger::logWalkExit(__CLASS_NAME__, this);
}

void NodeOptIOExpr::print(CompilerState &cs) {
	printFPIF(cs);
}

Register NodeOptIOExpr::genCode(CompilerState &cs, CodeGenArgs cg) {
	Logger::logGenCodeEntry(__CLASS_NAME__, this);

	Register r1(-1);
	genCodeAll(cs, cg);

	Logger::logGenCodeExit(__CLASS_NAME__, this);
	return r1;
}
