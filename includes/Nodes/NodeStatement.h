#ifndef SRC_NodeStatement_H_
#define SRC_NodeStatement_H_

#include "Nodes.h"

class NodeStatement: public NonTerminalNode {
public:
	NodeStatement() {
	}
	~NodeStatement() {
	}

	void print(CompilerState &cs) {
		if (!children.size())
			return;

		cs.os.printWhiteSpaces();

		if (children.size() == 3) {
			cs.os << '{';
			cs.os << '\n';

			cs.os.indent();
			children[1]->print(cs);
			cs.os.deindent();

			cs.os.printWhiteSpaces();
			cs.os << '}';
		} else
			printAllChildren(cs);

		cs.os << '\n';
	}

	static Node* parse(CompilerState &cs);
};

#endif
