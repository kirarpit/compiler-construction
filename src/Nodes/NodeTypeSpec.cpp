#include <AllNodeHeaders.h>

Node* NodeTypeSpec::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logParseEntry(__CLASS_NAME__, lex.peek());

	Node *typeSpec = NULL;

	Node *typeName = NodeTypeName::parse(cs);
	if (typeName) {
		typeSpec = new NodeTypeSpec();
		typeSpec->addNode(typeName);

		Node *arraySpecs = NodeOptArraySpecs::parse(cs);
		if (arraySpecs) {
			typeSpec->addNode(arraySpecs);
		} else {
			delete typeSpec;
			return NULL;
		}
	}

	Logger::logParseExit(__CLASS_NAME__, lex.peek());
	return typeSpec;
}

void NodeTypeSpec::walk(CompilerState &cs) {
	Logger::logWalkEntry(__CLASS_NAME__, this);

	walkAllChildren(cs);

	Logger::logWalkExit(__CLASS_NAME__, this);
}
