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
		XX(comma, ",", 0)  \
		XX(semi, ";", 0) \
		XX(colon, ":", 0) \
		XX(coloncolon, "::", 0)  \
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
		\
		XX(bool, "bool", 2)  \
		XX(break, "break", 2)  \
		XX(case, "case", 2)  \
		XX(continue, "continue", 2)  \
		XX(default, "default", 2)  \
		XX(do, "do", 2)  \
		XX(else, "else", 2)  \
		XX(false, "false", 2)  \
		XX(float, "float", 2)  \
		XX(if, "if", 2)  \
		XX(return, "return", 2)  \
		XX(signed, "signed", 2)  \
		XX(static, "static", 2)  \
		XX(struct, "struct", 2)  \
		XX(switch, "switch", 2)  \
		XX(true, "true", 2)  \
		XX(unsigned, "unsigned", 2)  \
		XX(var, "var", 2)  \
		XX(void, "void", 2)  \
		XX(while, "while", 2)  \
		\
		XX(underscore, "_", 3)	\
		XX(null, "\0", 3)  \
		XX(newline, "\n", 3)  \
		XX(empty, "\n", 3)  \

enum {
#define XX(a, b, c) TN_##a,
	TOKEN_LIST
	TN_COUNT
#undef XX
};

#define TOKEN_TYPE_LIST \
		XX(ILLCHR, "ILLCHR") \
		XX(EOF, "EOF") \
		XX(NUM, "Number")	\
		XX(ID, "Identifier")	\
		XX(KEY, "Keyword")	\
		XX(LIT, "Literal")

enum {
#define XX(a, b) TT_##a,
	TOKEN_TYPE_LIST
	TT_COUNT
#undef XX
};

class TokenTable {
public:
	TokenTable() {
	}
	virtual ~TokenTable() {
	}

	const static std::string TnInfo[];
	const static std::string TTInfo[];
};

#endif /* SRC_TOKENTABLE_H_ */
