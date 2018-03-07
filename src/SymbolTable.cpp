#include "SymbolTable.h"

void SymbolTable::enterScope() {
	SymbolTable *newST = new SymbolTable();
	newST->parent = st;
	st = newST;
}

void SymbolTable::exitScope() {
	if (st) {
		st = st->parent;
	}
}

SymbolTable* SymbolTable::getSymbolTable() {
	return st;
}

void SymbolTable::updateType(int name, std::string value) {
	TypeInfo *newType = new TypeInfo(name, value);
	newType->typeOf = st->type;
	st->type = newType;
}

void SymbolTable::insertVar(Token id) {
	if (st->variables.find(id) == st->variables.end()) {
		st->variables[id] = VariableInfo(st->type, VS_UNUSED);
	} else {
		st->variables.find(id)->second =
	}
}
