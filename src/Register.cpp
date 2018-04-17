#include<Register.h>
#include<CompilerState.h>
#include<OutputStream.h>

#define XX(a, b) b,
const std::string Register::RT[RT_COUNT] = {
REGISTER_TYPE_LIST };
#undef XX

void Register::print(CompilerState &cs) {
	if (offset != -1) {
		cs.os << offset << "(";
	}

	cs.os << "$" << RT[type];
	if (name != -1 && type != RT_GP)
		cs.os << name;

	if (offset != -1) {
		cs.os << ")";
	}
}
