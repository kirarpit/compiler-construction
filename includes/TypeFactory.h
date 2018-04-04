#ifndef SRC_TYPEFACTORY_H_
#define SRC_TYPEFACTORY_H_

#include<set>

class Type;

struct TypeCompare {
	bool operator()(const Type *lhs, const Type *rhs) const;
};

class TypeFactory {
public:
	TypeFactory();
	virtual ~TypeFactory();

	Type* getPrimType(int primType);
	Type* getArrayType(Type *t, int size);
	Type* getAddressType(Type *t);

private:

	std::set<Type*, TypeCompare> types;
	Type* find(Type *type);
};

#endif /* SRC_TYPEFACTORY_H_ */
