#ifndef SRC_TYPEFACTORY_H_
#define SRC_TYPEFACTORY_H_

#include<set>

class Type;

struct TypeCompare {
	bool operator()(const Type *lhs, const Type *rhs) const {
		return true;
	}
};

class TypeFactory {
public:
	TypeFactory();
	virtual ~TypeFactory();

	static Type* getPrimType(int primType);
	static Type* getArrayType(Type *t, int size);
	static Type* getAddressType(Type *t);

private:

	static std::set<Type*, TypeCompare> types;
	static Type* find(Type *type);
};

#endif /* SRC_TYPEFACTORY_H_ */
