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

	if (children.size() == 2) {
		if (children[0]->getToken().value == "--"
				|| children[0]->getToken().value == "++") {
			if (children[1]->getType()->isSigned()
					|| children[1]->getType()->isUnsigned()
					|| children[1]->getType()->isPointer()) {
				type = children[1]->getType();
			} else {
				//error
				exit(1);
			}

		} else if (children[0]->getToken().value == "-") {
			if (children[1]->getType()->isSigned()
					|| children[1]->getType()->isUnsigned()) {
				type = children[1]->getType();
			} else {
				//error
				exit(1);
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

		} else if (children[0]->getToken().value == "&") {
			if (!children[1]->isConstant) { //or maybe this should be ID only
				type = cs.tf.getAddressType(children[1]->getType());
			} else {
				//error
				exit(1);
			}
		}
	}

	Logger::logWalkExit(__CLASS_NAME__, this);
}
