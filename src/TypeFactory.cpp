#include<TypeFactory.h>
#include<Type.h>
#include<Logger.h>

TypeFactory::TypeFactory() {
	Logger::logConst(__CLASS_NAME__);
}

TypeFactory::~TypeFactory() {
	Logger::logDest(__CLASS_NAME__);

	std::set<Type*>::iterator it;
	for (it = types.begin(); it != types.end(); ++it) {
		delete *it;
	}
}

bool TypeCompare::operator()(const Type *lhs, const Type *rhs) const {
	//returns true if the first argument is considered to go before the
	//second in the strict weak ordering it defines, and false otherwise
	return (*lhs) < (*rhs);
}

Type* TypeFactory::find(Type *t) {
	std::set<Type*>::iterator iter = types.find(t);
	if (iter != types.end()) {
		return *iter;
	} else {
		return NULL;
	}
}

Type* TypeFactory::getPrimType(int primType) {
	Logger::log("blah");

	Type temp(primType);
	Type *foundType = find(&temp);

	if (foundType) {
		Logger::log("old primitive found %d", primType);
		return foundType;

	} else {
		Logger::log("new primitive type %d", primType);
		Type *newType = new Type(primType);
		types.insert(newType);
		return newType;
	}
}

Type* TypeFactory::getArrayType(Type *t, int size) {
	Logger::log("blah");

	Type temp(TP_ARRAY, size);
	temp.typeOf = t;
	Type *foundType = find(&temp);

	if (foundType) {
		Logger::log("old array type found");

		return foundType;
	} else {
		Logger::log("new array type");
		Type *newType = new Type(TP_ARRAY, size);
		newType->typeOf = t;

		types.insert(newType);
		return newType;
	}
}

Type* TypeFactory::getAddressType(Type *t) {
	Logger::log("blah");

	Type temp(TP_POINTER);
	temp.typeOf = t;
	Type *foundType = find(&temp);

	if (foundType) {
		Logger::log("old pointer type found");

		return foundType;
	} else {
		Logger::log("new pointer type");
		Type *newType = new Type(TP_POINTER);
		newType->typeOf = t;

		types.insert(newType);
		return newType;
	}
}
