#include<Node.h>
#include<VariableInfo.h>
#include<Logger.h>
#include<CompilerState.h>
#include<OutputStream.h>
#include <Type.h>

#define XX(a, b) b,
const std::string VariableInfo::VarStatInfo[VAR_STAT_CNT] = {
VAR_STAT_LIST };
#undef XX

VariableInfo::VariableInfo(int status, Type *type) :
		status(status), type(type) {
	Logger::logConst(__CLASS_NAME__);
}

VariableInfo::~VariableInfo() {
	Logger::logDest(__CLASS_NAME__);
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
