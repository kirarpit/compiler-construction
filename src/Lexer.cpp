#include <Lexer.h>
#include<iostream>
#include<InputStream.h>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include"TokenTable.h"

Lexer::Lexer(InputStream &in) :
		input(in), peeked(false) {
	singleByteLiterals = "()[]{}.,;:!?=<>&|^*%/+-";

	doubleByteLiterals.push_back("::");
	doubleByteLiterals.push_back("==");
	doubleByteLiterals.push_back("!=");
	doubleByteLiterals.push_back("<<");
	doubleByteLiterals.push_back(">>");
	doubleByteLiterals.push_back(">=");
	doubleByteLiterals.push_back("<=");
	doubleByteLiterals.push_back("&&");
	doubleByteLiterals.push_back("||");
	doubleByteLiterals.push_back("++");
	doubleByteLiterals.push_back("--");

#define XX(a,b,c) if(c==1){ \
		keywords.push_back(TS_##b); \
	}\
	TOKEN_LIST
#undef XX

	keywords.push_back(TS_bool);
	keywords.push_back("break");
	keywords.push_back("case");
	keywords.push_back("continue");
	keywords.push_back("default");
	keywords.push_back("do");
	keywords.push_back("else");
	keywords.push_back("false");
	keywords.push_back("float");
	keywords.push_back("if");
	keywords.push_back("return");
	keywords.push_back("signed");
	keywords.push_back("static");
	keywords.push_back("struct");
	keywords.push_back("switch");
	keywords.push_back("true");
	keywords.push_back("unsigned");
	keywords.push_back("var");
	keywords.push_back("void");
	keywords.push_back("while");
}

Lexer::~Lexer() {
}

bool Lexer::isSingleByteLiteral(char ch) {
	if (singleByteLiterals.find(ch) != string::npos) {
		return true;
	}
	return false;
}

bool Lexer::isDoubleByteLiteral(string str) {
	if (find(doubleByteLiterals.begin(), doubleByteLiterals.end(), str)
			!= doubleByteLiterals.end()) {
		return true;
	}
	return false;
}

bool Lexer::isKeyword(string str) {
	if (find(keywords.begin(), keywords.end(), str) != keywords.end()) {
		return true;
	}
	return false;
}

string Lexer::getLiteralType(string val) {
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

Token Lexer::tokenInit(string type, char ch) {
	string val = "";

	if (ch) {
		val.push_back(ch);
	}

	Token token(input.getStreamName(), input.getLineNumber(),
			input.getLocation() - 1, type, val);

	return token;
}

Token Lexer::tokenizeLiteral(char ch) {
	Token token = tokenInit("Literals", ch);

	if (isSingleByteLiteral(input.peek())) {
		if (isDoubleByteLiteral(token.value + input.peek())) {
			token.value.push_back(input.read());
		}
	}

	token.subType = getLiteralType(token.value);
	return token;
}

Token Lexer::tokenizeNumber(char ch) {
	Token token = tokenInit("Number", ch);

	bool dot_flag = false;
	while (isdigit(input.peek()) || (input.peek() == '.' && !dot_flag)) {
		if (input.peek() == '.')
			dot_flag = true;

		token.value += input.read();
	}

	return token;
}

Token Lexer::tokenizeKeywordOrID(char ch) {
	Token token = tokenInit("", ch);

	while (input.peek() == '_' || isalnum(input.peek())) {
		token.value += input.read();
	}
	if (isKeyword(token.value)) {
		token.type = "Keyword";
	} else {
		token.type = "Identifier";
	}

	return token;
}

Token Lexer::read() {
	if (peeked) {
		peeked = false;
		return myToken;
	}

	char ch;
	Token token;
	while (input >> ch) {

		if (ch == '/' && input.peek() == '/') {
			input.read();
			while (input.peek() != '\n' && !input.is_eof()) {
				input.read();
			}
			continue;
		} else if (isSingleByteLiteral(ch)) {
			token = tokenizeLiteral(ch);
		} else if (isdigit(ch)) {
			token = tokenizeNumber(ch);
		} else if (ch == '_' || isalnum(ch)) {
			token = tokenizeKeywordOrID(ch);
		} else if (isspace(ch)) {
			continue;
		} else {
			token = tokenInit("ILLCHR", ch);
		}

		return token;
	}

	if (input.is_eof()) {
		token = tokenInit("EOF", '\0');

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
