#include "Nodes/AllNodesHeader.h"

Node* NodeTypeSpec::parse(CompilerState &cs) {
	Lexer &lex = cs.lexer;
	Logger::logNodeEntry(__CLASS_NAME__, lex.peek());

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

	Logger::logNodeExit(__CLASS_NAME__, lex.peek());
	return typeSpec;
}
