#include "SymbolTable.h"

SymbolTable* SymbolTable::enterScope(Node *nodeBlock) {
	SymbolTable *newST = new SymbolTable();
	newST->parent = nodeBlock;
	return newST;
}

Node* SymbolTable::exitScope() {
	return parent;
}

void SymbolTable::updateVarType(int name, Node* node) {
	Logger::log("Updating Type of type: %d", name);

	TypeInfo *newType = new TypeInfo(name, node);
	newType->typeOf = varType;
	varType = newType;
}

void SymbolTable::insertVar(Token id) {
	Logger::log("Inserting an ID: " + id.value);

	if (isDef) {
		if (variables.find(id.value) == variables.end()) {
			variables[id.value] = VariableInfo(VS_UNUSED);
			variables.find(id.value)->second.setType(varType);
			varType = deepCopy(varType);
			varIDs.push_back(id.value);
		}
	} else {
		if (variables.find(id.value) != variables.end()) {
			variables.find(id.value)->second.status = VS_OKAY;
		} else {
			SymbolTable *foundST = lookup(id);
			if (foundST) {
				foundST->variables.find(id.value)->second.status = VS_OKAY;
			} else {
				variables[id.value] = VariableInfo(VS_UNDEC);
				variables.find(id.value)->second.setType(NULL);
			}
		}
	}
}

void SymbolTable::flush(bool error) {
	Logger::log("Flushing Type");
	if (varType)
		delete varType;
	varType = NULL;

	if (error) {
		while (!varIDs.empty()) {
			variables.erase(variables.find(varIDs.back()));
			varIDs.pop_back();
		}
	} else {
		varIDs.clear();
	}
}

void SymbolTable::print(CompilerState &cs) {
	Logger::log("Printing SymbolTable");

	for (std::map<std::string, VariableInfo>::iterator i = variables.begin();
			i != variables.end(); i++) {
		cs.os.printWhiteSpaces();
		cs.os << i->first << " ";
		i->second.print(cs);
		cs.os << '\n';
	}
}

TypeInfo* SymbolTable::deepCopy(TypeInfo *type) {
	Logger::log("DeepCopying the type");
	if (!type)
		return NULL;

	TypeInfo *newType = deepCopy(type->typeOf);
	TypeInfo *temp = new TypeInfo(type->name, type->value);
	temp->typeOf = newType;
	return temp;
}

SymbolTable* SymbolTable::lookup(Token id) {
	if (!parent) {
		return NULL;
	}

	if (parent->getST()->variables.find(id.value)
			!= parent->getST()->variables.end()) {
		return parent->getST();
	}

	return parent->getST()->lookup(id);
}
