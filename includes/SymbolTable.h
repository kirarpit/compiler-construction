#ifndef SRC_SYMBOLTABLE_H_
#define SRC_SYMBOLTABLE_H_

#include<map>
#include<CompilerState.h>
#include<VariableInfo.h>
#include<Token.h>
#include<TypeInfo.h>
#include<OutputStream.h>
#include<Nodes/Nodes.h>

class SymbolTable {
public:
	SymbolTable() :
			parent(NULL), isDef(true), type(NULL) {
	}
	virtual ~SymbolTable() {
	}

	SymbolTable *parent;

	SymbolTable* enterScope();
	SymbolTable* exitScope();
	void updateType(int name, Node* node);
	void insertVar(Token id);
	void flush();
	void print(CompilerState &cs);

	bool isDef;

	/*
	 * localLookup() checks in variables
	 * lookup() checks in parents else returns false
	 */

private:
	std::map<std::string, VariableInfo> variables;
	TypeInfo *type;
};

#endif /* SRC_SYMBOLTABLE_H_ */
