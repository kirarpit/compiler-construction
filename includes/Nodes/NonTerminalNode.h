#ifndef NODES_NONTERMINALNODE_H_
#define NODES_NONTERMINALNODE_H_

#include<Node.h>
#include<string>
#include<vector>

#include<Lexer.h>
#include<CompilerState.h>
#include<ErrorStream.h>
#include<Logger.h>
#include<TerminalNode.h>
#include<SymbolTable.h>
#include<TypeInfo.h>
#include<OutputStream.h>

class Node;
class CompilerState;

class NonTerminalNode: public Node {
public:
	NonTerminalNode();
	~NonTerminalNode();

	void print(CompilerState &cs) = 0;

	void addNode(Node *node);
	void walk(CompilerState &cs);
	Node* getChild(int index);
	int getSize();
	void clearChildren();
	void deleteChildren();

	void deleteChild(int index);

	bool findPostfixExpr();
	std::string getName();

protected:
	void printAllChildren(CompilerState &cs);
	void printParenthesised(CompilerState &cs);
	void printFPIF(CompilerState &cs);

	void operatorWalk(CompilerState &cs);

	std::vector<Node*> children;
};

#endif /* NODES_NONTERMINALNODE_H_ */
