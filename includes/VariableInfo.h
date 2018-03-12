#ifndef SRC_VARIABLEINFO_H_
#define SRC_VARIABLEINFO_H_

#include<string>
#include<TypeInfo.h>
#include<Nodes.h>

#define VAR_STAT_LIST \
	XX(UNUSED, "unused")	\
	XX(OKAY, "okay")	\
	XX(UNDEC, "undeclared")

#define XX(a, b) VS_##a,
enum {
	VAR_STAT_LIST
	VAR_STAT_CNT
};
#undef XX

class VariableInfo {
public:
	VariableInfo() :
			type(NULL), status(-1) {
		Logger::log("VariableInfo Constructor Called w/o arguments");
	}
	VariableInfo(int status) :
			type(NULL), status(status) {
		Logger::log("VariableInfo Constructor Called w/ 1 argument");
	}
	virtual ~VariableInfo() {
		Logger::log("VariableInfo Destructor Called");
		if (type)
			delete type;
	}

	const static std::string VarStatInfo[];

	void setType(TypeInfo *type);

	void print(CompilerState &cs);
	void recursiveTypePrint(CompilerState &cs, TypeInfo *type);
	TypeInfo *type;
	int status;
};

#endif /* SRC_VARIABLEINFO_H_ */
