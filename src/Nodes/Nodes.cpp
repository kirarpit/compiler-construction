#include "Nodes/AllNodesHeader.h"

void NodeSpike2::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::log("Parsing NodeSpike2, Token Value: " + lex.peek().value + "\n");

	while (lex.peek().type != "EOF") {
		Node *expr = NodeExpr::parse(cs);
		if (expr) {
			expr->print(cs.output);
			cs.output << endl;
			delete expr;
		}
		if (cs.error) {
			lex.recover();
			cs.error = false;
			continue;
		}
		if (lex.peek().value != ";") {
			cs.reportError();
			lex.recover();
			cs.error = false;
			continue;
		}
		Logger::log("Consumed Terminal:" + lex.peek().value + "\n");
		lex.read();
	}
}
