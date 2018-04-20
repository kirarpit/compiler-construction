#ifndef SRC_TYPEINFO_H_
#define SRC_TYPEINFO_H_

#include<string>

class Node;
class Token;
class CompilerState;

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

class Type {
public:
	Type(int name, int size = -1);
	virtual ~Type();

	const static std::string TS[];

	bool operator<(const Type &t) const;

	void print(CompilerState &cs);
	void shortPrint(CompilerState &cs);
	void recursivePrint(CompilerState &cs, Type *type, bool shortForm);

	Type* deref(CompilerState &cs, Token tn, int type);

	bool isSigned();
	bool isUnsigned();
	bool isBool();
	bool isPointer();
	bool isNumericType();

	int getFullSize();
	int getAlignment();

	static Type* getOperatorType(CompilerState &cs, Token tkn, Type *t1,
			Type *t2);
	static Node* constantFold(CompilerState &cs, Token tkn, Token t1, Token t2);

	int typeName;
	int size;
	Type *typeOf;
};

#endif /* SRC_TYPEINFO_H_ */
