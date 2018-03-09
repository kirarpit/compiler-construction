#ifndef SRC_VARIABLEINFO_H_
#define SRC_VARIABLEINFO_H_

#include<string>
#include<TypeInfo.h>
#include<OutputStream.h>
#include<Token.h>
#include<CompilerState.h>
#include<Nodes/Nodes.h>

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
	}
	VariableInfo(int status) :
			type(NULL), status(status) {
	}
	virtual ~VariableInfo() {
		Logger::log("VariableInfo Destructor Called");
	}

	const static std::string VarStatInfo[];

	void setType(TypeInfo *node);

	void print(CompilerState &cs);
	void recursiveTypePrint(CompilerState &cs, TypeInfo *type);
	TypeInfo *type;
	int status;
	Token tkn;
};

#endif /* SRC_VARIABLEINFO_H_ */
