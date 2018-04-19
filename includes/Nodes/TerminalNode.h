#ifndef NODES_TERMINALNODE_H_
#define NODES_TERMINALNODE_H_

#include<Node.h>
#include<Token.h>

class CompilerState;
class Logger;

class TerminalNode: public Node {
public:
	TerminalNode(Token tkn);
	~TerminalNode();

	void walk(CompilerState &cs);
	Register genCode(CompilerState &cs, CodeGenArgs cg);
	void print(CompilerState &cs);

	Token getToken();

protected:
	Token token;
};

#endif /* NODES_TERMINALNODE_H_ */
