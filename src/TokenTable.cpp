#include <TokenTable.h>

#define XX(a, b, c) b,
const std::string TokenTable::TS[TN_COUNT] = {
		TOKEN_LIST
};
#undef XX

#define XX(a, b, c) b,
const std::string TokenTable::TyInfo[TT_COUNT] = {
		TOKEN_TYPE_LIST
};
#undef XX
