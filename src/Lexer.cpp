#include <Lexer.h>
#include<iostream>
#include<InputStream.h>

Lexer::~Lexer() {
}

void Lexer::scan() {
	char ch;
	while (input >> ch) {

		if (ch == '/' && input.peek() == '/') { //comments check
			input.read();
			while (input.peek() != '\n' && !input.is_eof()) {
				input.read();
			}
			continue;
		}

		else if (isSingleByteLiteral(ch)) {
			string token = "";
			token.push_back(ch);
			if (isSingleByteLiteral(input.peek())) {
				if (isDoubleByteLiteral(token + input.peek())) {
					token.push_back(input.read());
				}
			}

			print(token, "Literal");
		}

		else if (isdigit(ch)) { //can't be literal, keyword, ID or internal
			string number = "";
			number += ch;
			bool dot_flag = false;
			while (isdigit(input.peek()) || (input.peek() == '.' && !dot_flag)) {
				if (input.peek() == '.')
					dot_flag = true;

				number += input.read();
			}
			print(number, "Number");
		}

		else if (ch == '_' || isalnum(ch)) {
			string token = "";
			token += ch;
			while (input.peek() == '_' || isalnum(input.peek())) {
				token += input.read();
			}
			string token_type;
			if (isKeyword(token)) {
				token_type = "Keyword";
			} else {
				token_type = "Identifier";
			}
			print(token, token_type);
		}

		else if (isspace(ch)) {
			continue;
		}

		else {
			string token = "";
			token.push_back(ch);
			print(token, "ILLCHR");
		}
	}

	if (input.is_eof())
		print("e", "EOF");
	else
		//possibly error occurred while reading some characters
		//or read some garbage values outside comments
		exit(1);
}

bool Lexer::isSingleByteLiteral(char ch) {
	if (strchr("()[]{}.,;:!?=!<>&|^*%/+-", ch)) {
		return true;
	}
	return false;
}

bool Lexer::isDoubleByteLiteral(string token) {
	string mylist[] = { "::", "==", "!=", "<<", ">>", ">=", "<=", "&&", "||",
			"++", "--" };

	string *begin = mylist;
	string *end = mylist + 11;

	if (find(begin, end, token) != end) {
		return true;
	}

	return false;
}

bool Lexer::isKeyword(string token) {
	string keywords[] = { "bool", "break", "case", "continue", "default", "do",
			"else", "false", "float", "if", "return", "signed", "static",
			"struct", "switch", "true", "unsigned", "var", "void", "while" };

	string *begin = keywords;
	string *end = keywords + 20;

	if (find(begin, end, token) != end) {
		return true;
	}

	return false;
}

void Lexer::print(string token, string token_type) {
	output << input.getFileName();
	output << ':';
	output << input.getLineNumber();
	output << ':';
	output << input.getLocation() - token.length();
	output << ':';

	if (token_type == "Number") {
		output << "$num:";
	} else if (token_type == "EOF") {
		output << "$EOF";
	} else if (token_type == "ILLCHR") {
		output << "$illchr:";
	} else if (token_type == "Identifier") {
		output << "$id:";
	}

	if (token_type != "EOF")
		output << token;
	output << endl;
}
