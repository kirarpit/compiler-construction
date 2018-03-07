#ifndef SRC_SYMBOLTABLE_H_
#define SRC_SYMBOLTABLE_H_

#include<map>
#include "VariableInfo.h"
#include "Token.h"
#include "TypeInfo.h"

class SymbolTable {
public:
	SymbolTable() :
			parent(NULL), st(this), type(NULL), isDef(true) {
	}
	virtual ~SymbolTable() {
	}

	SymbolTable *parent;

	void enterScope();
	void exitScope();
	SymbolTable* getSymbolTable();
	void updateType(int name, std::string value);
	void insertVar(Token id);

	std::string id;

	/*
	 * localLookup() checks in variables
	 * lookup() checks in parents else returns false
	 */

private:
	std::map<Token, VariableInfo> variables;
	SymbolTable *st;
	TypeInfo *type;
	bool isDef;
};

#endif /* SRC_SYMBOLTABLE_H_ */
