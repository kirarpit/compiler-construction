#include<NodeArraySize.h>
#include<NodeExpr.h>

Node* NodeArraySize::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logNodeEntry(__CLASS_NAME__, lex.peek());

	Node *arraySize = new NodeArraySize();

	if (lex.peek().value != TokenTable::TS[TN_clsbrk]) {
		Node *expr = NodeExpr::parse(cs);
		if (expr) {
			arraySize->addNode(expr);
		} else {
			delete arraySize;
			return NULL;
		}
	}

	Logger::logNodeExit(__CLASS_NAME__, lex.peek());
	return arraySize;
}
