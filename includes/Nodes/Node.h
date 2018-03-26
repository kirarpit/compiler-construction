#ifndef SRC_NODES_H_
#define SRC_NODES_H_

#include<stdio.h>

class CompilerState;
class SymbolTable;
class TypeInfo;
class Token;

class Node {
public:
	Node();
	virtual ~Node();

	virtual void print(CompilerState &cs) = 0;
	virtual void walk(CompilerState &cs) = 0;
	virtual void addNode(Node *node);
	virtual bool findPostfixExpr();
	virtual SymbolTable* getST();
	virtual Node* getChild(int index);
	virtual void clearChildren();
	virtual Token getToken();
	virtual int getSize();

	TypeInfo* getType();
	void setType(TypeInfo *t);
	bool isConstant;
	bool isTerminal;

protected:
	TypeInfo *type;
};

#endif /* SRC_NODES_H_ */
