#ifndef SRC_SYMBOLTABLE_H_
#define SRC_SYMBOLTABLE_H_

#include<map>
#include<vector>
#include<CompilerState.h>
#include<VariableInfo.h>

class Node;

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

	Node *parent;

	static SymbolTable* enterScope(Node *nodeBlock);
	Node* exitScope();
	void updateVarType(int name, Node* node);
	void insertVar(Token id);
	void flush(bool error);
	void print(CompilerState &cs);
	SymbolTable* lookup(Token id);

	bool isDef;

private:
	std::map<std::string, VariableInfo> variables;
	TypeInfo *varType;
	std::vector<std::string> varIDs;
	TypeInfo* deepCopy(TypeInfo *type);
};

#endif /* SRC_SYMBOLTABLE_H_ */
