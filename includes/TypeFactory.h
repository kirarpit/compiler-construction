#ifndef SRC_TYPEFACTORY_H_
#define SRC_TYPEFACTORY_H_

#include<iostream>
#include<set>
#include <stdio.h>
#include <iostream>
#include <string>
#include<vector>
#include<sstream>
#include<algorithm>
#include<set>

#include<iostream>
#include<set>
#include<vector>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<sstream>

class Type;

class TypeFactory {
public:
	TypeFactory();
	virtual ~TypeFactory();

	Type* getPrim(int type);
	Type* getArray(Type *t, int size);
	Type* getAddress(Type *t);


private:

	Type* initType(Type *t);
};

#endif /* SRC_TYPEFACTORY_H_ */
