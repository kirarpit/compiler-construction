#ifndef SRC_TYPEINFO_H_
#define SRC_TYPEINFO_H_

#include<string>
class Node;
class Token;

#define TYPE_LIST \
	XX(ARRAY, "array")	\
	XX(POINTER, "pointer")	\
	XX(BOOL, "bool")\
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
	TypeInfo(int name, int size = 0);
	virtual ~TypeInfo();

	const static std::string Type[];

	TypeInfo* addr();
	TypeInfo* deref(int type);
	bool isSigned();
	bool isUnsigned();
	bool isBool();
	bool isPointer();
	bool isNumericType();
	bool isEqual(TypeInfo *t1);

	static TypeInfo* getOperandType(Token tkn, TypeInfo *t1, TypeInfo *t2);
	static Node* constantFold(Token tkn, Node *n1, Node *n2);

	int type;
	int size;
	TypeInfo *typeOf;
};

#endif /* SRC_TYPEINFO_H_ */
