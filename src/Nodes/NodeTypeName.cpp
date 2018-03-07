#include "Nodes/AllNodesHeader.h"
#include "TypeInfo.h"

Node* NodeTypeName::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::log(
			"Parsing NodeTypeName, Token Value: " + lex.peek().value + "\n");

	Node *typeName = NULL;

	string primType = lex.peek().value;
	if (primType == Type[TP_BOOL] || primType == Type[TP_SIGNED]
			|| primType == Type[TP_UNSIGNED]) {
		typeName = new NodeTypeName();
		typeName->addNode(new TerminalNode(lex.read()));

		cs.st->updateType(PRIM, primType);
	} else {
		cs.reportError();
	}

	Logger::log(
			"Returning NodeTypeName, Token Value: " + lex.peek().value + "\n");
	return typeName;
}
