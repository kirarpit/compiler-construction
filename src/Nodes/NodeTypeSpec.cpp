#include "Nodes/AllNodesHeader.h"

Node* NodeTypeSpec::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logNodeEntry("NodeTypeSpec", lex.peek());

	Node *typeSpec = NULL;

	Node *typeName = NodeTypeName::parse(cs);
	if (typeName) {
		typeSpec = new NodeTypeSpec();
		typeSpec->addNode(typeName);

		Node *arraySpecs = NodeArraySpecs::parse(cs);
		if (arraySpecs) {
			typeSpec->addNode(arraySpecs);
		} else {
			delete typeSpec;
			return NULL;
		}
	}

	Logger::logNodeExit("NodeTypeSpec", lex.peek());
	return typeSpec;
}
