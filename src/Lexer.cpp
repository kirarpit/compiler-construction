#include <Lexer.h>
#include<iostream>
#include<InputStream.h>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>

Lexer::Lexer() {
	string literals = "()[]{}.,;:!?=<>&|^*%/+-";
	setSingleByteLiterals(literals);

	vector<string> doubleLiterals;
	doubleLiterals.push_back("::");
	doubleLiterals.push_back("==");
	doubleLiterals.push_back("!=");
	doubleLiterals.push_back("<<");
	doubleLiterals.push_back(">>");
	doubleLiterals.push_back(">=");
	doubleLiterals.push_back("<=");
	doubleLiterals.push_back("&&");
	doubleLiterals.push_back("||");
	doubleLiterals.push_back("++");
	doubleLiterals.push_back("--");
	setDoubleByteLiterals(doubleLiterals);

	vector<string> keywords;
	keywords.push_back("bool");
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
	setKeywords(keywords);
}

Lexer::~Lexer() {
}

void Lexer::setSingleByteLiterals(string literals) {
	singleByteLiterals = literals;
}

void Lexer::setDoubleByteLiterals(vector<string> doubleLiterals) {
	doubleByteLiterals = doubleLiterals;
}

void Lexer::setKeywords(vector<string> words) {
	keywords = words;
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

Token Lexer::tokenizeLiteral(InputStream &input, char ch) {
	string val = "";
	val.push_back(ch);
	int pos = input.getLocation() - 1;

	if (isSingleByteLiteral(input.peek())) {
		if (isDoubleByteLiteral(val + input.peek())) {
			val.push_back(input.read());
		}
	}

	Token token(input.getStreamName(), input.getLineNumber(), pos, "Literals",
			val);
	return token;
}

Token Lexer::tokenizeNumber(InputStream &input, char ch) {
	string number = "";
	number.push_back(ch);
	int pos = input.getLocation() - 1;

	bool dot_flag = false;
	while (isdigit(input.peek()) || (input.peek() == '.' && !dot_flag)) {
		if (input.peek() == '.')
			dot_flag = true;

		number += input.read();
	}

	Token token(input.getStreamName(), input.getLineNumber(), pos, "Number",
			number);
	return token;
}

Token Lexer::tokenizeKeywordOrID(InputStream &input, char ch) {
	string val = "";
	val.push_back(ch);
	int pos = input.getLocation() - 1;

	while (input.peek() == '_' || isalnum(input.peek())) {
		val += input.read();
	}
	string tokenType;
	if (isKeyword(val)) {
		tokenType = "Keyword";
	} else {
		tokenType = "Identifier";
	}

	Token token(input.getStreamName(), input.getLineNumber(), pos, tokenType,
			val);
	return token;
}

void Lexer::scan(InputStream &input, ostream &output) {
	char ch;
	Token token = Token();
	while (input >> ch) {

		if (ch == '/' && input.peek() == '/') {
			input.read();
			while (input.peek() != '\n' && !input.is_eof()) {
				input.read();
			}
			continue;
		}

		else if (isSingleByteLiteral(ch)) {
			token = tokenizeLiteral(input, ch);
		}

		else if (isdigit(ch)) {
			token = tokenizeNumber(input, ch);
		}

		else if (ch == '_' || isalnum(ch)) {
			token = tokenizeKeywordOrID(input, ch);
		}

		else if (isspace(ch)) {
			continue;
		}

		else {
			string val = "";
			val.push_back(ch);
			token = Token(input.getStreamName(), input.getLineNumber(),
					input.getLocation() - 1, "ILLCHR", val);
		}

		output << token.print();
	}

	if (input.is_eof()) {
		token = Token(input.getStreamName(), input.getLineNumber(),
				input.getLocation() - 1, "EOF", "");
		output << token.print();
	} else
		exit(1);
}
