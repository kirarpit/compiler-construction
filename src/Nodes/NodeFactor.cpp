#include<AllNodeHeaders.h>
#include<TypeFactory.h>

Node* NodeFactor::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

	Node *factor = new NodeFactor();
	if (lex.peek().type & TT_PREUN_OP) {
		factor->addNode(new TerminalNode(lex.read()));
		Node *nextFactor = NodeFactor::parse(cs);
		if (nextFactor) {
			factor->addNode(nextFactor);
		} else {
			delete factor;
			return NULL;
		}
	} else {
		Node *postfixExpr = NodePostfixExpr::parse(cs);
		if (postfixExpr) {
			factor->addNode(postfixExpr);
		} else {
			delete factor;
			return NULL;
		}
	}

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return factor;
}

void NodeFactor::walk(CompilerState &cs) {
	Logger::logWalkEntry(__CLASS_NAME__, this);

	smartWalk(cs);

	std::string val = children[0]->getToken().value;
	if (children.size() == 2) {
		Type *tp = children[1]->getType();

		if (val == TokenTable::TS[TN_minusminus]
				|| val == TokenTable::TS[TN_plusplus]) {

			if (tp->isSigned() || tp->isUnsigned() || tp->isPointer()) {
				type = tp;
			} else {
				cs.es.reportTypeError(cs, children[0]->getToken(), tp,
						"cannot pre increment/decrement value of type '%t'");
			}

		} else if (val == TokenTable::TS[TN_minus]) {
			if (tp->isSigned() || tp->isUnsigned()) {
				type = tp;
			} else {
				cs.es.reportTypeError(cs, children[0]->getToken(), tp,
						"invalid argument type '%t' to unary expression");
			}

			if (children[1]->isConstant) {
				int val = -1 * children[1]->getToken().getIntVal();
				std::ostringstream oss;
				oss << val;

				Node *terminalNode = new TerminalNode(Token(TT_NUM, oss.str()));
				terminalNode->setType(type);
				deleteChildren();
				addNode(terminalNode);
			}

		} else if (val == TokenTable::TS[TN_and]) {
			if (!children[1]->isConstant) { //or maybe this should be ID only
				type = cs.tf.getAddressType(tp);
			} else {
				cs.es.reportTypeError(cs, children[0]->getToken(), tp,
						"cannot take the address of an rvalue of type '%t'");
			}
		}
	}

	Logger::logWalkExit(__CLASS_NAME__, this);
}
