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
#include<OutputStream.h>
#include<Type.h>

class Node;
class CompilerState;

class NonTerminalNode: public Node {
public:
	NonTerminalNode();
	~NonTerminalNode();

	void print(CompilerState &cs) = 0;
	void walk(CompilerState &cs);

	void addNode(Node *node);
	Node* getChild(int index);
	int getSize();
	void clearChildren();
	void deleteChildren();

	void deleteChild(int index);
	void clearChild(int index);

	bool findPostfixExpr();
	std::string getName();

protected:
	void walkAllChildren(CompilerState &cs);

	void printAllChildren(CompilerState &cs);
	void printParenthesised(CompilerState &cs);
	void printFPIF(CompilerState &cs);

	void operatorWalk(CompilerState &cs);

	std::vector<Node*> children;
};

#endif /* NODES_NONTERMINALNODE_H_ */
