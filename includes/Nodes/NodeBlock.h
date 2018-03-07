#include "Nodes.h"

class NodeBlock: public NonTerminalNode {
public:
	NodeBlock() :
			st(NULL) {
	}
	~NodeBlock() {
	}

	void print(OutputStream &out) {
		for (unsigned int i = 0; i < children.size(); i++) {
			children[i]->print(out);
			if (!i) {
				out << '\n';
				out << '\n';
			}
		}
	}
	static Node* parse(CompilerState &cs);

	SymbolTable *st;
};
