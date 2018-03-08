#include "SymbolTable.h"

SymbolTable* SymbolTable::enterScope() {
	SymbolTable *newST = new SymbolTable();
	newST->parent = this;
	return newST;
}

SymbolTable* SymbolTable::exitScope() {
	return parent;
}

void SymbolTable::updateType(int name, std::string value) {
	TypeInfo *newType = new TypeInfo(name, value);
	newType->typeOf = type;
	type = newType;
}

void SymbolTable::insertVar(Token id) {
	if (isDef) {
		if (variables.find(id) == variables.end()) {
			variables[id] = VariableInfo(type, VS_UNUSED);
		}
	} else {
		if (variables.find(id) == variables.end()) {
			variables[id] = VariableInfo(type, VS_UNDEC);
		} else {
			variables.find(id)->second.status = VS_OKAY;
		}
	}
}

void SymbolTable::flush() {
	type = NULL;
}

void SymbolTable::print(OutputStream &os) {
	for (std::map<Token, VariableInfo>::iterator i = variables.begin();
			i != variables.end(); i++) {
		os << i->first << " ";
		i->second.print(os);
		os << '\n';
	}
}
