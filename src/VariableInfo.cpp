#include "VariableInfo.h"

#define XX(a, b) b,
const std::string VariableInfo::VarStatInfo[VAR_STAT_CNT] = {
		VAR_STAT_LIST
};
#undef XX

void VariableInfo::print(OutputStream &os) {
	os << VarStatInfo[status];
	os << " ";

	if (type == NULL) {
		os << "unknown";
	} else {
		recursiveTypePrint(os, type);
	}
}

void VariableInfo::recursiveTypePrint(OutputStream &os, TypeInfo *type) {
	if (!type) {
		return;
	}

	recursiveTypePrint(os, type->typeOf);
	if (type->name == ARRAY || type->name == POINTER) {
		os << "[" << type->value << "]";
	} else if (type->name == PRIM) {
		os << type->value;
	}
}
