#ifndef SRC_SYMBOLTABLE_H_
#define SRC_SYMBOLTABLE_H_

#include<set>
#include<map>
#include<vector>

class VariableInfo;
class Token;
class Type;

struct TokenCompare {
	bool operator()(const Token &t1, const Token &t2) const;
};

class SymbolTable {
public:
	SymbolTable();
	virtual ~SymbolTable();

	Node *parent;

	static SymbolTable* enterScope(Node *nodeBlock);
	Node* exitScope();
	void updateVarType(CompilerState &cs, int name, int size = -1);
	void insertOrUpdateVar(Token id);
	void print(CompilerState &cs);
	VariableInfo* lookup(Token id);
	VariableInfo* localLookup(Token id);

	bool isDef;

private:
	std::map<Token, VariableInfo, TokenCompare> variables;
	Type *varType;
};

#endif /* SRC_SYMBOLTABLE_H_ */
