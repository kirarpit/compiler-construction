#include "Nodes/AllNodesHeader.h"
#include "TypeInfo.h"

Node* NodeTypeName::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logNodeEntry("NodeTypeName", lex.peek());

	Node *typeName = NULL;

	std::string primType = lex.peek().value;
	if (primType == TypeInfo::Type[TP_BOOL]
			|| primType == TypeInfo::Type[TP_SIGNED]
			|| primType == TypeInfo::Type[TP_UNSIGNED]) {
		typeName = new NodeTypeName();
		typeName->addNode(new TerminalNode(lex.read()));

		cs.st->updateVarType(PRIM, typeName);
	} else {
		cs.es.reportError(cs);
	}

	Logger::logNodeExit("NodeTypeName", lex.peek());
	return typeName;
}
