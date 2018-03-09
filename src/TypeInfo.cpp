#include "TypeInfo.h"

void TypeInfo::initType() {

#define XX(a, b) Type[i] = b;
	for (int i = 0; i < TYPE_CNT; i++) {
		TYPE_LIST
	}
#undef XX

}
