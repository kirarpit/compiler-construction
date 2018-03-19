#include <AllNodeHeaders.h>

Node* NodeAsgnExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logNodeEntry(__CLASS_NAME__, lex.peek());

	Node *asgnExpr = new NodeAsgnExpr();

	Node *condOrPostfixExpr = NodeCondExpr::parse(cs);
	if (condOrPostfixExpr) {
		asgnExpr->addNode(condOrPostfixExpr);

		if (lex.peek().value == TokenTable::TS[TN_equal]) {
			//check if it's indeed PE
			if (!condOrPostfixExpr->findPostfixExpr()) {
				Logger::log(
						"CE can't be PE, Token Value: " + lex.peek().print());

				cs.es.reportParseError(cs);
				delete asgnExpr;
				return NULL;
			}
			Logger::log("CE can be PE, Token Value: " + lex.peek().print());

			asgnExpr->addNode(new TerminalNode(lex.read()));

			Node *nextAsgnExpr = NodeAsgnExpr::parse(cs);
			if (nextAsgnExpr) {
				asgnExpr->addNode(nextAsgnExpr);
			} else {
				delete asgnExpr;
				return NULL;
			}
		}
	} else {
		delete asgnExpr;
		return NULL;
	}

	Logger::logNodeExit(__CLASS_NAME__, lex.peek());
	return asgnExpr;
}

//void NodeAsgnExpr::walk() {
//	TypeInfo *types[children.size()];
//
//	for (unsigned int i = 0; i < children.size(); i++) {
//		types[i] = children[i]->walk();
//	}
//
//	if (children.size > 1)
//		type = children[0]->getType();
//	else
//		type = TypeInfo::getOperandType(TN_equal, types[0], types[2]);
//}
