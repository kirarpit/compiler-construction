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
	VariableInfo(int status = -1, Type *type = NULL, int offset = 0);
	virtual ~VariableInfo();

	const static std::string VarStatInfo[];
	void print(CompilerState &cs);
	int getSize();
	int getAlignment();

	int status;
	Type *type;
	int offset;
};

#endif /* SRC_VARIABLEINFO_H_ */
