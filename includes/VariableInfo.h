#ifndef SRC_VARIABLEINFO_H_
#define SRC_VARIABLEINFO_H_

#include<string>

class TypeInfo;
class CompilerState;

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
	VariableInfo();
	VariableInfo(int status);
	virtual ~VariableInfo();

	const static std::string VarStatInfo[];

	void setType(TypeInfo *type);

	void print(CompilerState &cs);
	void recursiveTypePrint(CompilerState &cs, TypeInfo *type);
	TypeInfo *type;
	int status;
};

#endif /* SRC_VARIABLEINFO_H_ */
