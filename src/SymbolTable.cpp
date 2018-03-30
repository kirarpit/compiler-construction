#include<Node.h>
#include<SymbolTable.h>
#include<Logger.h>
#include<CompilerState.h>
#include<VariableInfo.h>
#include<OutputStream.h>
#include <Type.h>

SymbolTable::SymbolTable() :
		parent(NULL), isDef(true), varType(NULL) {
	Logger::log("SymbolTable Constructor Called");
}

SymbolTable::~SymbolTable() {
	Logger::log("SymbolTable Destructor Called");
	if (varType)
		delete varType;
}

SymbolTable* SymbolTable::enterScope(Node *nodeBlock) {
	SymbolTable *newST = new SymbolTable();
	newST->parent = nodeBlock;
	return newST;
}

Node* SymbolTable::exitScope() {
	return parent;
}

void SymbolTable::updateVarType(int name, int size = 0) {
	Logger::log("Updating Type of type: %d", name);

	Type *newType = new Type(name, size);
	newType->typeOf = varType;
	varType = newType;
}

void SymbolTable::insertVar(Token id) {
	Logger::log("Inserting/Updating an ID: " + id.value);

	if (isDef) {
		if (!localLookup(id)) {
			variables[id.value] = VariableInfo(VS_UNUSED);
			variables[id.value].setType(varType);

			varType = deepCopy(varType);
			varIDs.push_back(id.value);
		} else {
			//error
			//just gotta ignore it and throw std error which will increase the count
			exit(1);
		}
	} else {
		VariableInfo *varPtr = lookup(id);
		if (varPtr) {
			varPtr->status = VS_OKAY;
		} else {
			//error
			//this is still parsing, can return bool and throw an error while parsing
			//which will hopefully roll back and remove the entire statement
			exit(1);
			variables[id.value] = VariableInfo(VS_UNDEC);
			variables[id.value].setType(NULL);
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
	for (std::map<std::string, VariableInfo>::iterator i = variables.begin();
			i != variables.end(); i++) {
		cs.os.printWhiteSpaces();
		cs.os << i->first << " ";
		i->second.print(cs);
		cs.os << '\n';
	}
}

Type* SymbolTable::deepCopy(Type *type) {
	Logger::log("DeepCopying the type");
	if (!type)
		return NULL;

	Type *newType = deepCopy(type->typeOf);
	Type *temp = new Type(type->type, type->size);
	temp->typeOf = newType;
	return temp;
}

VariableInfo* SymbolTable::lookup(Token id) {
	VariableInfo *var = localLookup(id);
	if (var)
		return var;

	if (!parent)
		return NULL;

	return parent->getST()->lookup(id);
}

VariableInfo* SymbolTable::localLookup(Token id) {
	if (variables.find(id.value) != variables.end())
		return &variables[id.value];

	return NULL;
}
