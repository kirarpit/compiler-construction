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
		if (variables.find(id.value) == variables.end()) {
			variables.insert(
					std::pair<std::string, VariableInfo>(id.value,
							VariableInfo(type, VS_UNUSED)));
		}
	} else {
		if (variables.find(id.value) == variables.end()) {
			variables.insert(
					std::pair<std::string, VariableInfo>(id.value,
							VariableInfo(type, VS_UNDEC)));
		} else {
			variables.find(id.value)->second.status = VS_OKAY;
		}
	}
}

void SymbolTable::flush() {
	type = NULL;
}

void SymbolTable::print(CompilerState &cs) {
	for (std::map<std::string, VariableInfo>::iterator i = variables.begin();
			i != variables.end(); i++) {
		cs.output << i->first << " ";
		i->second.print(cs);
		cs.output << '\n';
	}
}
