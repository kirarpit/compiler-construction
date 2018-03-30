#include <AllNodeHeaders.h>
#include <Type.h>

Node* NodeTypeName::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

	Node *typeName = NULL;

	std::string primType = lex.peek().value;
	if (primType == Type::TS[TP_BOOL]
			|| primType == Type::TS[TP_SIGNED]
			|| primType == Type::TS[TP_UNSIGNED]) {

		int name;
		if (primType == Type::TS[TP_SIGNED]) {
			name = TP_SIGNED;
		} else if (primType == Type::TS[TP_UNSIGNED]) {
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
