#include "SymbolTable.h"

SymbolTable* SymbolTable::enterScope() {
	SymbolTable *newST = new SymbolTable();
	newST->parent = this;
	return newST;
}

SymbolTable* SymbolTable::exitScope() {
	return parent;
}

void SymbolTable::updateType(int name, Node* node) {
	Logger::log("Updating Type Number %d", name);
	TypeInfo *newType = new TypeInfo(name, node);
	newType->typeOf = type;
	type = newType;
}

void SymbolTable::insertVar(Token id) {
	Logger::log("Inserting an ID:" + id.value);

	if (isDef) {
		if (variables.find(id.value) == variables.end()) {
			variables[id.value] = VariableInfo(VS_UNUSED);
			variables.find(id.value)->second.setType(type);
		}
	} else {
		if (variables.find(id.value) == variables.end()) {
			variables[id.value] = VariableInfo(VS_UNDEC);
			variables.find(id.value)->second.setType(type);
		} else {
			variables.find(id.value)->second.status = VS_OKAY;
		}
	}
}

void SymbolTable::flush() {
	Logger::log("Flushing Type value where bool(type) is %d", type ? 1 : 0);

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
