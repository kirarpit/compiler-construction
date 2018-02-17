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
	return new TerminalNode(cs.lexer.read());
}

