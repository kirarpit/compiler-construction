#include "Nodes.h"

class NodeStatement: public NonTerminalNode {
public:
	NodeStatement() {
	}
	~NodeStatement() {
	}

	void print(CompilerState &cs) {
		cs.output.printWhiteSpaces();

		if (children.size() == 3) {
			cs.output << '{';
			cs.output << '\n';

			cs.output.indent();
			children[1]->print(cs);
			cs.output.deindent();

			cs.output.printWhiteSpaces();
			cs.output << '}';
		} else
			printAllChildren(cs);

		cs.output << '\n';
	}

	static Node* parse(CompilerState &cs);
};
