#ifndef SRC_REGISTER_H_
#define SRC_REGISTER_H_

#include<string>

#define REGISTER_TYPE_LIST \
	XX(EVAL, "v") \
	XX(ARG, "a") \
	XX(TEMP, "t") \
	XX(S_TEMP, "s") \
	XX(GP, "gp") \

enum {
#define XX(a, b) RT_##a,
	REGISTER_TYPE_LIST
	RT_COUNT
#undef XX
};

class CompilerState;

class Register {
public:
	Register(int name, int type = -1, int offset = -1) :
			name(name), type(type), offset(offset) {
	}
	virtual ~Register() {
	}

	int name;
	int type;
	int offset;

	const static std::string RT[];

	void print(CompilerState &cs);
};

#endif /* SRC_REGISTER_H_ */
