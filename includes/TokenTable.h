#ifndef SRC_TOKENTABLE_H_
#define SRC_TOKENTABLE_H_

#include<string>

#define TOKEN_LIST \
		XX(opnpar, "(", TT_LIT) \
		XX(clspar, ")", TT_LIT) \
		XX(opnbrk, "[", TT_LIT) \
		XX(clsbrk, "]", TT_LIT) \
		XX(opnbrc, "{", TT_LIT) \
		XX(clsbrc, "}", TT_LIT) \
		XX(dot, ".", TT_LIT)  \
		XX(comma, ",", TT_LIT)  \
		XX(semi, ";", TT_LIT) \
		XX(colon, ":", TT_LIT) \
		XX(coloncolon, "::", TT_LIT)  \
		XX(bang, "!", TT_LIT) \
		XX(quest, "?", TT_LIT)  \
		XX(equal, "=", TT_LIT)  \
		XX(equalequal, "==", TT_LIT | TT_EQ_OP)  \
		XX(notequal, "!=", TT_LIT | TT_EQ_OP)  \
		XX(leftshift, "<<", TT_LIT) \
		XX(rightshift, ">>", TT_LIT)  \
		XX(gtr, ">", TT_LIT | TT_REL_OP)  \
		XX(lss, "<", TT_LIT | TT_REL_OP)  \
		XX(gtrequal, ">=", TT_LIT | TT_REL_OP)  \
		XX(lssequal, "<=", TT_LIT | TT_REL_OP)  \
		XX(and, "&", TT_LIT | TT_PREUN_OP)  \
		XX(andand, "&&", TT_LIT)  \
		XX(or, "|", TT_LIT) \
		XX(oror, "||", TT_LIT)  \
		XX(xor, "^", TT_LIT)  \
		XX(star, "*", TT_LIT | TT_FACTOR_OP) \
		XX(mod, "%", TT_LIT)  \
		XX(slash, "/", TT_LIT | TT_FACTOR_OP)  \
		XX(plus, "+", TT_LIT | TT_TERM_OP) \
		XX(minus, "-", TT_LIT | TT_TERM_OP | TT_PREUN_OP)  \
		XX(plusplus, "++", TT_LIT | TT_PREUN_OP | TT_POSTUN_OP)  \
		XX(minusminus, "--", TT_LIT | TT_PREUN_OP | TT_POSTUN_OP)	\
		\
		XX(bool, "bool", TT_KEY)  \
		XX(break, "break", TT_KEY)  \
		XX(case, "case", TT_KEY)  \
		XX(continue, "continue", TT_KEY)  \
		XX(default, "default", TT_KEY)  \
		XX(do, "do", TT_KEY)  \
		XX(else, "else", TT_KEY)  \
		XX(false, "false", TT_KEY)  \
		XX(float, "float", TT_KEY)  \
		XX(if, "if", TT_KEY)  \
		XX(return, "return", TT_KEY)  \
		XX(signed, "signed", TT_KEY)  \
		XX(static, "static", TT_KEY)  \
		XX(struct, "struct", TT_KEY)  \
		XX(switch, "switch", TT_KEY)  \
		XX(true, "true", TT_KEY)  \
		XX(unsigned, "unsigned", TT_KEY)  \
		XX(var, "var", TT_KEY)  \
		XX(void, "void", TT_KEY)  \
		XX(while, "while", TT_KEY)  \
		\
		XX(underscore, "_", TT_OTHER)	\
		XX(null, "\0", TT_OTHER)  \
		XX(newline, "\n", TT_OTHER)  \
		XX(empty, "\n", TT_OTHER)  \

enum {
#define XX(a, b, c) TN_##a,
	TOKEN_LIST
	TN_COUNT
#undef XX
};

#define TOKEN_TYPE_LIST \
		XX(LIT, "LITERAL", 0x0001)	\
		XX(KEY, "KEYWORD", 0x0002)	\
		XX(NUM, "NUMBER", 0x0004)	\
		XX(ID, "IDENTIFIER", 0x0008)	\
		XX(ILLCHR, "ILLCHR", 0x0010) \
		XX(EOF, "EOF", 0x0020) \
		XX(TERM_OP, "TERM_OP", 0x0040) \
		XX(FACTOR_OP, "FACTOR_OP", 0x0080) \
		XX(EQ_OP, "EQ_OP", 0x0100) \
		XX(REL_OP, "REL_OP", 0x0200) \
		XX(PREUN_OP, "PREUN_OP", 0x0400) \
		XX(POSTUN_OP, "POSTUN_OP", 0x0800) \
		XX(OTHER, "OTHER", 0x1000) \

enum {
#define XX(a, b, c) TT_##a = c,
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
