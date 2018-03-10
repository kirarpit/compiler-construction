#include <Lexer.h>

Lexer::Lexer(InputStream &in) :
		input(in), peeked(false) {

#define XX(a, b, c)	\
	if (c & TT_LIT) {	\
		literals.insert(b);	\
	} else if (c & TT_KEY){	\
		keywords.insert(b);	\
	}
	TOKEN_LIST
#undef XX
}

Lexer::~Lexer() {
}

bool Lexer::isLiteral(std::string str) {
	if (literals.find(str) != literals.end()) {
		return true;
	}
	return false;
}

bool Lexer::isKeyword(std::string str) {
	if (keywords.find(str) != keywords.end()) {
		return true;
	}
	return false;
}

std::string Lexer::getLiteralType(std::string val) {
	if (val == "+" || val == "-") {
		return "TERM_OP";
	} else if (val == "*" || val == "/") {
		return "FACTOR_OP";
	} else if (val == "==" || val == "!=") {
		return "EQ_OP";
	} else if (val == "<" || val == "<=" || val == ">" || val == ">=") {
		return "REL_OP";
	} else if (val == "-" || val == "&") {
		return "PREUN_OP";
	} else if (val == "--" || val == "++") {
		return "POSTUN_OP";
	}

	return "";
}

Token Lexer::tokenInit(int type, std::string val) {
	Token token(input.getStreamName(), input.getLineNumber(),
			input.getLocation() - 1, type, val);

	return token;
}

Token Lexer::tokenizeLiteral(std::string val) {
	Token token = tokenInit(TT_LIT, val);

	if (isLiteral(input.peek()) && isLiteral(val + input.peek())) {
		token.value += input.read();
	}

	token.subType = getLiteralType(token.value);
	return token;
}

Token Lexer::tokenizeNumber(std::string val) {
	Token token = tokenInit(TT_NUM, val);

	bool dot_flag = false;
	while (isdigit(input.peek()[0])
			|| (input.peek() == TokenTable::TnInfo[TN_dot] && !dot_flag)) {
		if (input.peek() == TokenTable::TnInfo[TN_dot])
			dot_flag = true;

		token.value += input.read();
	}

	return token;
}

Token Lexer::tokenizeKeywordOrID(std::string str) {
	Token token = tokenInit(-1, str);

	while (input.peek() == TokenTable::TnInfo[TN_underscore]
			|| isalnum(input.peek()[0])) {
		token.value += input.read();
	}
	if (isKeyword(token.value)) {
		token.type = TT_KEY;
	} else {
		token.type = TT_ID;
	}

	return token;
}

Token Lexer::read() {
	if (peeked) {
		peeked = false;
		return myToken;
	}

	std::string str;
	Token token;
	while (input >> str) {

		if (str == TokenTable::TnInfo[TN_slash]
				&& input.peek() == TokenTable::TnInfo[TN_slash]) {
			input.read();
			while (input.peek() != TokenTable::TnInfo[TN_newline]
					&& !input.is_eof()) {
				input.read();
			}
			continue;

		} else if (isLiteral(str)) {
			token = tokenizeLiteral(str);

		} else if (isdigit(str[0])) {
			token = tokenizeNumber(str);

		} else if (str == TokenTable::TnInfo[TN_underscore]
				|| isalnum(str[0])) {
			token = tokenizeKeywordOrID(str);

		} else if (isspace(str[0])) {
			continue;

		} else {
			token = tokenInit(TT_ILLCHR, str);
		}

		return token;
	}

	if (input.is_eof()) {
		token = tokenInit(TT_EOF, TokenTable::TnInfo[TN_null]);

		return token;
	} else
		exit(1);
}

Token Lexer::peek() {
	if (peeked)
		return myToken;

	myToken = read();
	peeked = true;
	return myToken;
}
