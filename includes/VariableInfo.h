#ifndef SRC_VARIABLEINFO_H_
#define SRC_VARIABLEINFO_H_

#include<string>

class Type;
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

	void setType(Type *type);

	void print(CompilerState &cs);
	Type *type;
	int status;
};

#endif /* SRC_VARIABLEINFO_H_ */
