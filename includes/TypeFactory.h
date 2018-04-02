#ifndef SRC_TYPEFACTORY_H_
#define SRC_TYPEFACTORY_H_

#include<set>

class Type;

class TypeFactory {
public:
	TypeFactory();
	virtual ~TypeFactory();

	Type* getPrim(int type);
	Type* getArray(Type *t, int size);
	Type* getAddress(Type *t);

private:

	std::set<int> a;
	Type* initType(Type *t);
};

#endif /* SRC_TYPEFACTORY_H_ */
