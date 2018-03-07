#ifndef SRC_TYPEINFO_H_
#define SRC_TYPEINFO_H_

#include<string>

enum {
	PRIM, ARRAY, POINTER
};

#define TYPE_LIST \
	XX(BOOL, "bool")	\
	XX(SIGNED, "signed")	\
	XX(UNSIGNED, "unsigned")

#define XX(a, b) TP_##a,
enum {
	TYPE_LIST
	TYPE_CNT
};
#undef XX

#define XX(a, b) b,
std::string Type[TYPE_CNT] = {
		TYPE_LIST
};
#undef XX

class TypeInfo {
public:
	TypeInfo(int name, std::string value) :
			name(name), value(value), typeOf(NULL) {
	}
	virtual ~TypeInfo() {
	}

	int name;
	std::string value;
	TypeInfo *typeOf;
};

#endif /* SRC_TYPEINFO_H_ */
