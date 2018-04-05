#include<Node.h>
#include<SymbolTable.h>
#include<Logger.h>
#include<CompilerState.h>
#include<VariableInfo.h>
#include<OutputStream.h>
#include<Type.h>
#include<TypeFactory.h>

SymbolTable::SymbolTable() :
		parent(NULL), isDef(true), varType(NULL) {
	Logger::logConst(__CLASS_NAME__);
}

SymbolTable::~SymbolTable() {
	Logger::logDest(__CLASS_NAME__);
}

SymbolTable* SymbolTable::enterScope(Node *nodeBlock) {
	SymbolTable *newST = new SymbolTable();
	newST->parent = nodeBlock;
	return newST;
}

Node* SymbolTable::exitScope() {
	return parent;
}

void SymbolTable::updateVarType(CompilerState &cs, int name, int size) {
	Logger::log("Updating Type of type: %d", name);
	Logger::log("and size %d", size);

	if (name == TP_BOOL || name == TP_SIGNED || name == TP_UNSIGNED) {
		varType = cs.tf.getPrimType(name);
	} else if (name == TP_ARRAY) {
		varType = cs.tf.getArrayType(varType, size);
	} else if (name == TP_POINTER) {
		varType = cs.tf.getAddressType(varType);
	}
}

void SymbolTable::insertOrUpdateVar(Token id) {
	Logger::log("Inserting/Updating an ID: " + id.value);

	if (isDef) {
		if (!localLookup(id)) {
			variables[id.value] = VariableInfo(VS_UNUSED, varType);
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
		}
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
