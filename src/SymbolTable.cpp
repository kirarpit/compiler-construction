#include<SymbolTable.h>
#include<Node.h>
#include<Logger.h>
#include<CompilerState.h>
#include<VariableInfo.h>
#include<OutputStream.h>
#include<Type.h>
#include<TypeFactory.h>
#include<ErrorStream.h>

SymbolTable::SymbolTable() :
		parent(NULL), isDef(true), varType(NULL), lastVar(NULL) {
	Logger::logConst(__CLASS_NAME__);
}

SymbolTable::~SymbolTable() {
	Logger::logDest(__CLASS_NAME__);
}

bool TokenCompare::operator()(const Token &t1, const Token &t2) const {
	return t1 < t2;
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

bool SymbolTable::insertOrUpdateVar(CompilerState &cs, Token id) {
	Logger::log("Inserting/Updating an ID: " + id.value);
	if (isDef) {
		if (!localLookup(id)) {
			VariableInfo newVar(VS_UNUSED, varType);
			newVar.offset = computeOffset(newVar);
			variables[id] = newVar;
			lastVar = &variables[id];

		} else {
			cs.es.reportDeclError(cs, id);
			return false;
		}
	} else {
		VariableInfo *varPtr = lookup(id);
		if (varPtr) {
			varPtr->status = VS_OKAY;
		} else {
			cs.es.reportDeclError(cs, id);
			return false;
		}
	}

	return true;
}

void SymbolTable::print(CompilerState &cs) {
	for (std::map<Token, VariableInfo>::iterator i = variables.begin();
			i != variables.end(); i++) {
		cs.os.printWhiteSpaces();
		cs.os << i->first.value << " ";
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
	if (variables.find(id) != variables.end())
		return &variables[id];

	return NULL;
}

int SymbolTable::computeOffset(VariableInfo &var) {
	Logger::log("Computing Offset");

	VariableInfo *varX = getLastVar();
	if (varX)
		return (getLastVar()->offset + getLastVar()->getSize()
				+ var.getAlignment() - 1) / var.getAlignment()
				* var.getAlignment();
	else
		return (var.getAlignment() - 1) / var.getAlignment()
				* var.getAlignment();
}

VariableInfo* SymbolTable::getLastVar() {
	if (lastVar)
		return lastVar;

	if (!parent)
		return NULL;

	return parent->getST()->getLastVar();
}
