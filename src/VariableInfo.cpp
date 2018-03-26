#include<Node.h>
#include<VariableInfo.h>
#include<Logger.h>
#include<CompilerState.h>
#include<TypeInfo.h>
#include<OutputStream.h>

#define XX(a, b) b,
const std::string VariableInfo::VarStatInfo[VAR_STAT_CNT] = {
VAR_STAT_LIST };
#undef XX

VariableInfo::VariableInfo() :
		type(NULL), status(-1) {
	Logger::log("VariableInfo Constructor Called w/o arguments");
}

VariableInfo::VariableInfo(int status) :
		type(NULL), status(status) {
	Logger::log("VariableInfo Constructor Called w/ 1 argument");
}

VariableInfo::~VariableInfo() {
	Logger::log("VariableInfo Destructor Called");
	if (type)
		delete type;
}

void VariableInfo::setType(TypeInfo *typeInfo) {
	type = typeInfo;
}

void VariableInfo::print(CompilerState &cs) {
	cs.os << VarStatInfo[status];
	cs.os << " ";

	if (type == NULL) {
		cs.os << "unknown";
	} else {
		type->print(cs);
	}
}
