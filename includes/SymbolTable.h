#ifndef SRC_SYMBOLTABLE_H_
#define SRC_SYMBOLTABLE_H_

#include<string>
#include<set>
#include<map>
#include<vector>

class VariableInfo;
class Token;
class Type;

class SymbolTable {
public:
	SymbolTable();
	virtual ~SymbolTable();

	Node *parent;

	static SymbolTable* enterScope(Node *nodeBlock);
	Node* exitScope();
	void updateVarType(int name, int size);
	void insertVar(Token id);
	void flush(bool error);
	void print(CompilerState &cs);
	VariableInfo* lookup(Token id);
	VariableInfo* localLookup(Token id);

	bool isDef;

private:
	std::map<std::string, VariableInfo> variables;
	Type *varType;
	std::vector<std::string> varIDs;
	Type* deepCopy(Type *type);
};

#endif /* SRC_SYMBOLTABLE_H_ */
