#include <AllNodeHeaders.h>

Node* NodeLogorExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

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

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return logorExpr;
}

void NodeLogorExpr::walk(CompilerState &cs) {
	Logger::logWalkEntry(__CLASS_NAME__, this);

	smartWalk(cs);

	Logger::logWalkExit(__CLASS_NAME__, this);
}

void NodeLogorExpr::genCode(CompilerState &cs) {
	Logger::logGenCodeEntry(__CLASS_NAME__, this);

	Logger::logGenCodeExit(__CLASS_NAME__, this);
}
