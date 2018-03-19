#include <TokenTable.h>

#define XX(a, b, c) b,
const std::string TokenTable::TS[TN_COUNT] = {
		TOKEN_LIST
};
#undef XX
