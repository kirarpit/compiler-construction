#ifndef SRC_TOKENTABLE_H_
#define SRC_TOKENTABLE_H_

#include<string>

#define TOKEN_LIST \
		XX(opnpar, "(", 0) \
		XX(clspar, ")", 0) \
		XX(opnbrk, "[", 0) \
		XX(clsbrk, "]", 0) \
		XX(opnbrc, "{", 0) \
		XX(clsbrc, "}", 0) \
		XX(dot, ".", 0)  \
		XX(comma, ", ", 0)  \
		XX(semi, ";", 0) \
		XX(colon, "", 0) \
		XX(coloncolon, "", 0)  \
		XX(bang, "!", 0) \
		XX(quest, "?", 0)  \
		XX(equal, "=", 0)  \
		XX(equalequal, "==", 0)  \
		XX(notequal, "!=", 0)  \
		XX(leftshift, "<<", 0) \
		XX(rightshift, ">>", 0)  \
		XX(gtr, ">", 0)  \
		XX(lss, "<", 0)  \
		XX(gtrequal, ">=", 0)  \
		XX(lssequal, "<=", 0)  \
		XX(and, "&", 0)  \
		XX(andand, "&&", 0)  \
		XX(or, "|", 0) \
		XX(oror, "||", 0)  \
		XX(xor, "^", 0)  \
		XX(star, "*", 0) \
		XX(mod, "%", 0)  \
		XX(slash, "/", 0)  \
		XX(plus, "+", 0) \
		XX(minus, "-", 0)  \
		XX(plusplus, "++", 0)  \
		XX(minusminus, "--", 0)	\
		XX(bool, "bool", 1)  \
		XX(break, "break", 1)  \
		XX(case, "case", 1)  \
		XX(continue, "continue", 1)  \
		XX(default, "default", 1)  \
		XX(do, "do", 1)  \
		XX(else, "else", 1)  \
		XX(false, "false", 1)  \
		XX(float, "float", 1)  \
		XX(if, "if", 1)  \
		XX(return, "return", 1)  \
		XX(signed, "signed", 1)  \
		XX(static, "static", 1)  \
		XX(struct, "struct", 1)  \
		XX(switch, "switch", 1)  \
		XX(true, "true", 1)  \
		XX(unsigned, "unsigned", 1)  \
		XX(var, "var", 1)  \
		XX(void, "void", 1)  \
		XX(while, "while", 1)  \

enum TOKEN_ID {
#define XX(a, b, c) TN_##a,
	TN_COUNT
#undef XX
};

#define XX(a, b, c) const std::string TS_##a=b;
TOKEN_LIST
#undef XX

class TokenTable {
public:
	TokenTable();
	virtual ~TokenTable();
};

#endif /* SRC_TOKENTABLE_H_ */
