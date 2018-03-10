#include <Lexer.h>

Lexer::Lexer(InputStream &in) :
		input(in), peeked(false) {

#define XX(a, b, c)	\
	if (c & TT_LIT) {	\
		literals[b] = c;	\
	} else if (c & TT_KEY){	\
		keywords[b] = c;	\
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

Token Lexer::tokenInit(int type, std::string val) {
	Token token(input.getStreamName(), input.getLineNumber(),
			input.getLocation() - 1, type, val);

	return token;
}

Token Lexer::tokenizeLiteral(std::string val) {
	if (isLiteral(input.peek()) && isLiteral(val + input.peek())) {
		val += input.read();
	}

	return tokenInit(literals[val], val);
}

Token Lexer::tokenizeNumber(std::string val) {
	bool dot_flag = false;
	while (isdigit(input.peek()[0])
			|| (input.peek() == TokenTable::TS[TN_dot] && !dot_flag)) {
		if (input.peek() == TokenTable::TS[TN_dot])
			dot_flag = true;

		val += input.read();
	}

	return tokenInit(TT_NUM, val);
}

Token Lexer::tokenizeKeywordOrID(std::string val) {
	while (input.peek() == TokenTable::TS[TN_underscore]
			|| isalnum(input.peek()[0])) {
		val += input.read();
	}
	if (isKeyword(val)) {
		return tokenInit(TT_KEY, val);
	} else {
		return tokenInit(TT_ID, val);
	}
}

Token Lexer::read() {
	if (peeked) {
		peeked = false;
		return myToken;
	}

	std::string str;
	while (input >> str) {

		if (str == TokenTable::TS[TN_slash]
				&& input.peek() == TokenTable::TS[TN_slash]) {
			input.read();
			while (input.peek() != TokenTable::TS[TN_newline] && !input.is_eof()) {
				input.read();
			}
			continue;

		} else if (isLiteral(str)) {
			return tokenizeLiteral(str);

		} else if (isdigit(str[0])) {
			return tokenizeNumber(str);

		} else if (str == TokenTable::TS[TN_underscore] || isalnum(str[0])) {
			return tokenizeKeywordOrID(str);

		} else if (isspace(str[0])) {
			continue;

		} else {
			return tokenInit(TT_ILLCHR, str);
		}
	}

	if (input.is_eof()) {
		return tokenInit(TT_EOF, TokenTable::TS[TN_null]);
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
