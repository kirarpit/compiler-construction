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
			parent(NULL), isDef(true), varType(NULL) {
	}
	virtual ~SymbolTable() {
		if (varType)
			delete varType;
	}

	SymbolTable *parent;

	SymbolTable* enterScope();
	SymbolTable* exitScope();
	void updateVarType(int name, Node* node);
	void insertVar(Token id);
	void flush();
	void print(CompilerState &cs);
	TypeInfo* deepCopy(TypeInfo *type);

	bool isDef;

private:
	std::map<std::string, VariableInfo> variables;
	TypeInfo *varType;
};

#endif /* SRC_SYMBOLTABLE_H_ */
