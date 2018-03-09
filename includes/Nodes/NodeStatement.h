#include "Nodes.h"

class NodeStatement: public NonTerminalNode {
public:
	NodeStatement() {
	}
	~NodeStatement() {
	}

	void print(CompilerState &cs) {
		out.printWhiteSpaces();

		if (children.size() == 3) {
			out << '{';
			out << '\n';

			out.indent();
			children[1]->print(out);
			out.deindent();

			out.printWhiteSpaces();
			out << '}';
		} else
			printAllChildren(out);

		out << '\n';
	}

	static Node* parse(CompilerState &cs);
};
