#ifndef SRC_SYMBOLTABLE_H_
#define SRC_SYMBOLTABLE_H_

#include<map>
#include<vector>
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
		Logger::log("SymbolTable Constructor Called");

	}
	virtual ~SymbolTable() {
		Logger::log("SymbolTable Destructor Called");
		if (varType)
			delete varType;
	}

	SymbolTable *parent;

	SymbolTable* enterScope();
	SymbolTable* exitScope();
	void updateVarType(int name, Node* node);
	void insertVar(Token id);
	void flush(bool error);
	void print(CompilerState &cs);

	bool isDef;

private:
	std::map<std::string, VariableInfo> variables;
	TypeInfo *varType;
	std::vector<std::string> varIDs;
	TypeInfo* deepCopy(TypeInfo *type);
};

#endif /* SRC_SYMBOLTABLE_H_ */
