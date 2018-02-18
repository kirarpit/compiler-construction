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

	while (lex.peek().value == ",") {
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
	bool condExpr = false;
	Node *asgnExpr = new NodeAsgnExpr();

	lex.mark();

	//ignore errors
	Node *postfixExpr = NodePostfixExpr::parse(cs);
	if (postfixExpr && lex.peek().value == "=") {
		asgnExpr->addNode(postfixExpr);
		asgnExpr->addNode(new TerminalNode(lex.read()));

		Node *nextAsgnExpr = NodeAsgnExpr::parse(cs);
		if (nextAsgnExpr) {
			asgnExpr->addNode(nextAsgnExpr);
		} else {
			condExpr = true;
		}
	} else {
		condExpr = true;
	}
	//un-ignore errors

	if (condExpr) {
		if (!lex.set())
			return NULL;

		Node *condExpr = NodeCondExpr::parse(cs);
		if (condExpr) {
			asgnExpr->addNode(condExpr);
		} else {
			delete asgnExpr;
			return NULL;
		}
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
				if (cs.reportError() > 9) {
					exit(10);
				}
				errorFlag = true;
			}

		} else {
			errorFlag = true;
		}
	}

	if (errorFlag) {
		delete condExpr;
		return NULL;
	}

	return condExpr;
}

Node* NodeLogorExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Node *logorExpr = new NodeLogorExpr();

	Node *logandExpr = NodeLogandExpr::parse(cs);
	if (logandExpr) {
		logorExpr->addNode(logandExpr);
	} else {
		delete logorExpr;
		return NULL;
	}

	while (lex.peek().value == "||") {
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

	return logorExpr;
}

Node* NodeLogandExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Node *logandExpr = new NodeLogandExpr();

	Node *eqExpr = NodeEqExpr::parse(cs);
	if (eqExpr) {
		logandExpr->addNode(eqExpr);
	} else {
		delete logandExpr;
		return NULL;
	}

	while (lex.peek().value == "&&") {
		Node *tempLogandExpr = new NodeLogandExpr();

		tempLogandExpr->addNode(logandExpr);
		tempLogandExpr->addNode(new TerminalNode(lex.read()));
		Node *eqExpr = NodeEqExpr::parse(cs);
		if (eqExpr) {
			tempLogandExpr->addNode(eqExpr);
		} else {
			delete tempLogandExpr;
			return NULL;
		}

		logandExpr = tempLogandExpr;
	}

	return logandExpr;
}

Node* NodeEqExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Node *eqExpr = new NodeEqExpr();

	Node *relExpr = NodeRelExpr::parse(cs);
	if (relExpr) {
		eqExpr->addNode(relExpr);
	} else {
		delete eqExpr;
		return NULL;
	}

	while (lex.peek().value == "&&") {
		Node *tempEqExpr = new NodeEqExpr();

		tempEqExpr->addNode(eqExpr);
		tempEqExpr->addNode(new TerminalNode(lex.read()));
		Node *relExpr = NodeRelExpr::parse(cs);
		if (relExpr) {
			tempEqExpr->addNode(relExpr);
		} else {
			delete tempEqExpr;
			return NULL;
		}

		eqExpr = tempEqExpr;
	}

	return eqExpr;
}

Node* NodeRelExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Node *relExpr = new NodeRelExpr();

	Node *simpleExpr = NodeSimpleExpr::parse(cs);
	if (simpleExpr) {
		relExpr->addNode(simpleExpr);
	} else {
		delete relExpr;
		return NULL;
	}

	while (lex.peek().subType == "REL_OP") {
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

	return relExpr;
}

Node* NodeSimpleExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Node *simpleExpr = new NodeSimpleExpr();

	Node *term = NodeTerm::parse(cs);
	if (term) {
		simpleExpr->addNode(term);
	} else {
		delete simpleExpr;
		return NULL;
	}

	while (lex.peek().subType == "TERM_OP") {
		Node *tempSimpleExpr = new NodeSimpleExpr();

		tempSimpleExpr->addNode(simpleExpr);
		tempSimpleExpr->addNode(new TerminalNode(lex.read()));
		Node *term = NodeTerm::parse(cs);
		if (term) {
			tempSimpleExpr->addNode(term);
		} else {
			delete tempSimpleExpr;
			return NULL;
		}

		simpleExpr = tempSimpleExpr;
	}

	return simpleExpr;
}

Node* NodeTerm::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Node *term = new NodeTerm();

	Node *factor = NodeFactor::parse(cs);
	if (factor) {
		term->addNode(factor);
	} else {
		delete term;
		return NULL;
	}

	while (lex.peek().subType == "FACTOR_OP") {
		Node *tempTerm = new NodeTerm();

		tempTerm->addNode(term);
		tempTerm->addNode(new TerminalNode(lex.read()));
		Node *factor = NodeFactor::parse(cs);
		if (factor) {
			tempTerm->addNode(factor);
		} else {
			delete tempTerm;
			return NULL;
		}

		term = tempTerm;
	}

	return term;
}

Node* NodeFactor::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Node *factor = new NodeFactor();

	if (lex.peek().subType == "PREUN_OP" || lex.peek().subType == "POSTUN_OP") {
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

	return factor;
}

Node* NodePostfixExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Node *postfixExpr = new NodePostfixExpr();

	Node *primaryExpr = NodePrimaryExpr::parse(cs);
	if (primaryExpr) {
		postfixExpr->addNode(primaryExpr);
	} else {
		delete postfixExpr;
		return NULL;
	}

	while (1) {
		if (lex.peek().subType == "POSTUN_OP") {
			Node *tempPostfixExpr = new NodePostfixExpr();

			tempPostfixExpr->addNode(postfixExpr);
			tempPostfixExpr->addNode(new TerminalNode(lex.read()));

			postfixExpr = tempPostfixExpr;
		} else {
			//mute errors
			Node *arraySpec = NodeArraySpec::parse(cs);
			//unmute errors

			if (arraySpec) {
				Node *tempPostfixExpr = new NodePostfixExpr();

				tempPostfixExpr->addNode(postfixExpr);
				tempPostfixExpr->addNode(arraySpec);

				postfixExpr = tempPostfixExpr;
			} else {
				break;
			}
		}
	}

	return postfixExpr;
}

Node* NodeArraySpec::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	bool errorFlag = false;
	Node *arraySpec = new NodeArraySpec();

	if (lex.peek().value == "[") {
		arraySpec->addNode(new TerminalNode(lex.read()));

		arraySpec->addNode(NodeArraySize::parse(cs));

		if (lex.peek().value == "]") {
			arraySpec->addNode(new TerminalNode(lex.read()));
		} else {
			errorFlag = true;
		}

	} else {
		errorFlag = true;
	}

	if (errorFlag) {
		if (cs.reportError() > 9) {
			exit(10);
		}
		delete arraySpec;
		return NULL;
	}

	return arraySpec;
}

Node* NodeArraySize::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Node *arraySize = new NodeArraySize();

	//mute
	Node *expr = NodeExpr::parse(cs);
	//unmute
	if (expr) {
		arraySize->addNode(expr);
	} else {
		arraySize->addNode(new TerminalNode(lex.getToken("")));
	}

	return arraySize;
}

Node* NodePrimaryExpr::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	bool errorFlag = false;
	Node *primaryExpr = new NodePrimaryExpr();

	if (lex.peek().type == "Identifier") {
		primaryExpr->addNode(new TerminalNode(lex.read()));
	} else if (lex.peek().type == "Number") {
		primaryExpr->addNode(new TerminalNode(lex.read()));
	} else if (lex.peek().value == "(") {
		primaryExpr->addNode(new TerminalNode(lex.read()));

		Node *expr = NodeExpr::parse(cs);
		if (expr) {
			primaryExpr->addNode(expr);

			if (lex.peek().value == ")") {
				primaryExpr->addNode(new TerminalNode(lex.read()));
			} else {
				errorFlag = true;
				if (cs.reportError() > 9) {
					exit(10);
				}
			}
		} else {
			errorFlag = true;
		}
	} else {
		errorFlag = true;
		if (cs.reportError() > 9) {
			exit(10);
		}
	}

	if (errorFlag) {
		delete primaryExpr;
		return NULL;
	}

	return primaryExpr;
}
