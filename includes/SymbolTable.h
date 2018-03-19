#ifndef SRC_SYMBOLTABLE_H_
#define SRC_SYMBOLTABLE_H_

#include<map>
#include<vector>

class VariableInfo;
class Token;

class SymbolTable {
public:
	SymbolTable();
	virtual ~SymbolTable();

	Node *parent;

	static SymbolTable* enterScope(Node *nodeBlock);
	Node* exitScope();
	void updateVarType(int name, Node* node);
	void insertVar(Token id);
	void flush(bool error);
	void print(CompilerState &cs);
	VariableInfo* lookup(Token id);
	VariableInfo* localLookup(Token id);

	bool isDef;

private:
	std::map<std::string, VariableInfo> variables;
	TypeInfo *varType;
	std::vector<std::string> varIDs;
	TypeInfo* deepCopy(TypeInfo *type);
};

#endif /* SRC_SYMBOLTABLE_H_ */
