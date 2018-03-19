#include<TypeInfo.h>
#include<Logger.h>

TypeInfo::TypeInfo(int name, Node* node) :
		name(name), value(node), typeOf(NULL) {
	Logger::log("TypeInfo Constructor Called");
}

TypeInfo::~TypeInfo() {
	Logger::log("TypeInfo Destructor Called");
	if (typeOf)
		delete typeOf;
}

#define XX(a, b) b,
const std::string TypeInfo::Type[] = { TYPE_LIST };
#undef XX
