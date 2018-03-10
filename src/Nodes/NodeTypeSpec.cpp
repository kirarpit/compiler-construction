#include "Nodes/AllNodesHeader.h"

Node* NodeTypeSpec::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::log("Parsing NodeTypeSpec, Token Value: " + lex.peek().value);

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

	Logger::log("Returning NodeTypeSpec, Token Value: " + lex.peek().value);
	return typeSpec;
}
