#include <AllNodeHeaders.h>
#include "TypeInfo.h"

Node* NodeTypeName::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

	Node *typeName = NULL;

	std::string primType = lex.peek().value;
	if (primType == TypeInfo::Type[TP_BOOL]
			|| primType == TypeInfo::Type[TP_SIGNED]
			|| primType == TypeInfo::Type[TP_UNSIGNED]) {

		int name;
		if (primType == TypeInfo::Type[TP_SIGNED]) {
			name = TP_SIGNED;
		} else if (primType == TypeInfo::Type[TP_UNSIGNED]) {
			name = TP_UNSIGNED;
		} else {
			name = TP_BOOL;
		}
		cs.lastBlock->getST()->updateVarType(name, 0);

		typeName = new NodeTypeName();
		typeName->addNode(new TerminalNode(lex.read()));

	} else {
		cs.es.reportParseError(cs);
	}

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return typeName;
}
