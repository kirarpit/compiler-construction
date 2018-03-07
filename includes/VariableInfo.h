#ifndef SRC_VARIABLEINFO_H_
#define SRC_VARIABLEINFO_H_

#include<string>
#include<TypeInfo.h>

#define VAR_STAT_LIST \
	XX(UNUSED, "unused")	\
	XX(OKAY, "okay")	\
	XX(UNDEC, "undeclared")	\

#define XX(a, b) VS_##a,
enum {
	VAR_STAT_LIST
	VAR_STAT_CNT
};
#undef XX

#define XX(a, b) b,
std::string VarStatInfo[VAR_STAT_CNT] = {
		VAR_STAT_LIST
};
#undef XX

class VariableInfo {
public:
	VariableInfo(TypeInfo type, int status) :
			type(type), status(status) {
	}
	virtual ~VariableInfo() {
	}

	TypeInfo *type;
	int status;
};

#endif /* SRC_VARIABLEINFO_H_ */
