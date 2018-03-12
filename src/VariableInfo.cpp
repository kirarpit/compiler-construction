#include "VariableInfo.h"

#define XX(a, b) b,
const std::string VariableInfo::VarStatInfo[VAR_STAT_CNT] = {
VAR_STAT_LIST };
#undef XX

void VariableInfo::setType(TypeInfo *typeInfo) {
	type = typeInfo;
}

void VariableInfo::print(CompilerState &cs) {
	Logger::log("Printing VariableInfo");

	cs.os << VarStatInfo[status];
	cs.os << " ";

	if (type == NULL) {
		cs.os << "unknown";
	} else {
		recursiveTypePrint(cs, type);
	}
}

void VariableInfo::recursiveTypePrint(CompilerState &cs, TypeInfo *type) {
	Logger::log("Recursively Printing Type");
	if (!type) {
		return;
	}

	recursiveTypePrint(cs, type->typeOf);
	type->value->print(cs);
}
