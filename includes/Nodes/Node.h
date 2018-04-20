#ifndef SRC_NODES_H_
#define SRC_NODES_H_

#include<stdio.h>

class CompilerState;
class SymbolTable;
class Type;
class Token;
class Register;
class CodeGenArgs;

class Node {
public:
	Node();
	virtual ~Node();

	virtual void print(CompilerState &cs) = 0;
	virtual void walk(CompilerState &cs) = 0;
	virtual Register genCode(CompilerState &cs, CodeGenArgs cg);

	virtual void addNode(Node *node);
	virtual void clearChildren();
	virtual void deleteChildren();
	virtual void deleteChild(int index);
	virtual Node* getChild(int index);
	virtual Token getToken();
	virtual int getSize();
	Type* getType();
	void setType(Type *t);

	virtual bool isRemovable();
	virtual bool isEmpty();

	virtual SymbolTable* getST();
	virtual bool findPostfixExpr();

	void assignable();

	bool isConstant;
	bool isTerminal;
	bool isAssignable;

protected:
	Type *type;
};

#endif /* SRC_NODES_H_ */
