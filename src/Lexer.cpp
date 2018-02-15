#include <Lexer.h>
#include<iostream>
#include<InputStream.h>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>

Lexer::Lexer() {
	singleByteLiterals = "()[]{}.,;:!?=<>&|^*%/+-";

	string literals[] = { "::", "==", "!=", "<<", ">>", ">=", "<=", "&&", "||",
			"++", "--" };

	vector<string> tempLiterals(std::begin(literals), std::end(literals));
	doubleByteLiterals = tempLiterals;

	string keys[] = { "bool", "break", "case", "continue", "default", "do",
			"else", "false", "float", "if", "return", "signed", "static",
			"struct", "switch", "true", "unsigned", "var", "void", "while" };

	vector<string> tempKeywords(std::begin(keys), std::end(keys));
	keywords = tempKeywords;
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

Token Lexer::tokenInit(InputStream &input, string type, char ch) {
	string val = "";

	if (ch) {
		val.push_back(ch);
	}

	Token token(input.getStreamName(), input.getLineNumber(),
			input.getLocation() - 1, type, val);

	return token;
}

Token Lexer::tokenizeLiteral(InputStream &input, char ch) {
	Token token = tokenInit(input, "Literals", ch);

	if (isSingleByteLiteral(input.peek())) {
		if (isDoubleByteLiteral(token.value + input.peek())) {
			token.value.push_back(input.read());
		}
	}

	return token;
}

Token Lexer::tokenizeNumber(InputStream &input, char ch) {
	Token token = tokenInit(input, "Number", ch);

	bool dot_flag = false;
	while (isdigit(input.peek()) || (input.peek() == '.' && !dot_flag)) {
		if (input.peek() == '.')
			dot_flag = true;

		token.value += input.read();
	}

	return token;
}

Token Lexer::tokenizeKeywordOrID(InputStream &input, char ch) {
	Token token = tokenInit(input, "", ch);

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

void Lexer::scan(InputStream &input, ostream &output) {
	char ch;
	Token token;
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
			token = tokenInit(input, "ILLCHR", ch);
		}

		output << token.print();
	}

	if (input.is_eof()) {
		token = tokenInit(input, "EOF", '\0');
		output << token.print();
	} else
		exit(1);
}
