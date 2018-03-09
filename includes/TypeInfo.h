#ifndef SRC_TYPEINFO_H_
#define SRC_TYPEINFO_H_

#include<string>
class Node;

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

class TypeInfo {
public:
	TypeInfo(int name, Node* node) :
			name(name), value(node), typeOf(NULL) {
	}
	virtual ~TypeInfo() {
	}

	const static std::string Type[];
	int name;
	Node* value;
	TypeInfo *typeOf;
};

#endif /* SRC_TYPEINFO_H_ */
