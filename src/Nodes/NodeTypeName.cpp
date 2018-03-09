#include "Nodes/AllNodesHeader.h"
#include "TypeInfo.h"

Node* NodeTypeName::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::log(
			"Parsing NodeTypeName, Token Value: " + lex.peek().value);

	Node *typeName = NULL;

	std::string primType = lex.peek().value;
	if (primType == TypeInfo::Type[TP_BOOL] || primType == TypeInfo::Type[TP_SIGNED]
			|| primType == TypeInfo::Type[TP_UNSIGNED]) {
		typeName = new NodeTypeName();
		typeName->addNode(new TerminalNode(lex.read()));

		cs.st->updateVarType(PRIM, typeName);
	} else {
		cs.reportError();
	}

	Logger::log(
			"Returning NodeTypeName, Token Value: " + lex.peek().value);
	return typeName;
}
