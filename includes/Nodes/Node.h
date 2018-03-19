#ifndef SRC_NODES_H_
#define SRC_NODES_H_

#include<stdio.h>

class CompilerState;
class SymbolTable;
class TypeInfo;

class Node {
public:
	Node();
	virtual ~Node();

	virtual void print(CompilerState &cs) = 0;
	virtual void walk(CompilerState &cs) = 0;
	virtual void addNode(Node *node);
	virtual bool findPostfixExpr();
	virtual SymbolTable* getST();

	TypeInfo* getType();

protected:
	TypeInfo *type;
};

#endif /* SRC_NODES_H_ */
