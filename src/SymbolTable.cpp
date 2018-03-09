#include "SymbolTable.h"

SymbolTable* SymbolTable::enterScope() {
	SymbolTable *newST = new SymbolTable();
	newST->parent = this;
	return newST;
}

SymbolTable* SymbolTable::exitScope() {
	return parent;
}

void SymbolTable::updateVarType(int name, Node* node) {
	Logger::log("Updating Type: " + TypeInfo::Type[name]);

	if (name == PRIM) {
		varType = new TypeInfo(name, node);
	} else {
		TypeInfo *newType = new TypeInfo(name, node);
		newType->typeOf = varType;
		varType = newType;
	}
}

void SymbolTable::insertVar(Token id) {
	Logger::log("Inserting an ID: " + id.value);

	if (isDef) {
		if (variables.find(id.value) == variables.end()) {
			variables[id.value] = VariableInfo(VS_UNUSED);
			variables.find(id.value)->second.setType(varType);
		}
	} else {
		if (variables.find(id.value) == variables.end()) {
			variables[id.value] = VariableInfo(VS_UNDEC);
			variables.find(id.value)->second.setType(varType);
		} else {
			if (variables.find(id.value)->second.status == VS_UNUSED)
				variables.find(id.value)->second.status = VS_OKAY;
		}
	}
}

void SymbolTable::flush() {
	Logger::log("Flushing Type value where bool(type) is %d", varType ? 1 : 0);
	delete varType;
}

void SymbolTable::print(CompilerState &cs) {
	for (std::map<std::string, VariableInfo>::iterator i = variables.begin();
			i != variables.end(); i++) {
		cs.output << i->first << " ";
		i->second.print(cs);
		cs.output << '\n';
	}
}
