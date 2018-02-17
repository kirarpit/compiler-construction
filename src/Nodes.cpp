#include "Nodes.h"

void NodeSpike2::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;

	while (lex.peek().type != "EOF") {
		Node *expr = NodeExpr::parse(cs);
		if (expr) {
			expr->print(cs.output);
			delete expr;
		}
		if (cs.error) {
			lex.recover();
			cs.error = false;
			continue;
		}
		if (lex.peek().value != ";") {
			if (cs.reportError() > 9) {
				exit(10);
			}

			lex.recover();
			cs.error = false;
			continue;
		}
		lex.read();
	}
}

Node* NodeExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Node *expr = new NodeExpr();

	Node *asgnExpr = NodeAsgnExpr::parse(cs);
	if (asgnExpr) {
		expr->addNode(asgnExpr);
	} else {
		delete expr;
		return NULL;
	}

	if (cs.error)
		return expr;

	while (lex.peek().value == ",") {
		Node *tempExpr = new NodeExpr();

		tempExpr->addNode(expr);
		tempExpr->addNode(new TerminalNode(lex.read()));
		Node *asgnExpr = NodeAsgnExpr::parse(cs);
		if (asgnExpr) {
			tempExpr->addNode(asgnExpr);
		} else {
			return tempExpr;
		}

		if (cs.error)
			return tempExpr;

		expr = tempExpr;
	}

	return expr;
}

void NodeExpr::print(OutputStream &out) {
	if (children.size() > 1) {
		out << '(';

		unsigned int i;
		for (i = 0; i < children.size(); i++) {
			if (i == 0 || i == 2)
				children[i]->print(out);
			else if (i == 1)
				out << ',';
		}

		if (i == 3)
			out << ')';

	} else {
		for (unsigned int i = 0; i < children.size(); i++) {
			children[i]->print(out);
		}
	}
}

Node* NodeAsgnExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	bool errorFlag = false;
	Node *asgnExpr = new NodeAsgnExpr();

	lex.mark();
	Node *postfixExpr = NodePostfixExpr::parse(cs);
	if (postfixExpr && lex.peek().value == "=") {
		asgnExpr->addNode(postfixExpr);
		asgnExpr->addNode(new TerminalNode(lex.read()));

		Node *nextAsgnExpr = NodeAsgnExpr::parse(cs);
		if (nextAsgnExpr) {
			asgnExpr->addNode(nextAsgnExpr);
		} else {
			errorFlag = true;
		}
	} else {
		if (!lex.set())
			return NULL;

		Node *condExpr = NodeCondExpr::parse(cs);
		if (condExpr) {
			asgnExpr->addNode(condExpr);
		} else {
			errorFlag = true;
		}
	}

	if (errorFlag) {
		delete asgnExpr;
		if (cs.reportError() > 9) {
			exit(10);
		}
		return NULL;
	}

	return asgnExpr;
}

Node* NodeCondExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	bool errorFlag = false;
	Node *condExpr = new NodeCondExpr();

	Node *logorExpr = NodeLogorExpr::parse(cs);
	if (logorExpr) {
		condExpr->addNode(logorExpr);
	} else {
		delete condExpr;
		return NULL;
	}

	if (lex.peek().value == "?") {
		condExpr->addNode(new TerminalNode(lex.read()));

		Node *expr = NodeExpr::parse(cs);
		if (expr) {
			condExpr->addNode(expr);
			if (lex.peek().value == ":") {
				condExpr->addNode(new TerminalNode(lex.read()));

				Node *nextCondExpr = NodeCondExpr::parse(cs);
				if (nextCondExpr) {
					condExpr->addNode(nextCondExpr);
				} else {
					errorFlag = true;
				}

			} else {
				errorFlag = true;
			}

		} else {
			errorFlag = true;
		}
	}

	if (errorFlag) {
		delete condExpr;
		if (cs.reportError() > 9) {
			exit(10);
		}
		return NULL;
	}

	return condExpr;
}

Node* NodeLogorExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	bool errorFlag = false;
	Node *logorExpr = new NodeLogorExpr();

	return logorExpr;
}
