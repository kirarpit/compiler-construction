#include "VariableInfo.h"

#define XX(a, b) b,
const std::string VariableInfo::VarStatInfo[VAR_STAT_CNT] = {
		VAR_STAT_LIST
};
#undef XX

void VariableInfo::print(CompilerState &cs) {
	cs.output << VarStatInfo[status];
	cs.output << " ";

	if (type == NULL) {
		cs.output << "unknown";
	} else {
		recursiveTypePrint(cs, type);
	}
}

void VariableInfo::recursiveTypePrint(CompilerState &cs, TypeInfo *type) {
	if (!type) {
		return;
	}

	recursiveTypePrint(cs, type->typeOf);
	if (type->name == ARRAY || type->name == POINTER) {
		type->value->print(cs);
	} else if (type->name == PRIM) {
		type->value->print(cs);
	}
}
