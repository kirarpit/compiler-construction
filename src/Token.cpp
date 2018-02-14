#include "Token.h"

Token::~Token() {
}

std::string Token::print() {
	std::string output;
	output = filename + ":" + std::to_string(line) + ":"
			+ std::to_string(position) + ":";

	if (tokenType == "Number") {
		output += "$num:";
	} else if (tokenType == "EOF") {
		output += "$EOF";
	} else if (tokenType == "ILLCHR") {
		output += "$illchr:";
	} else if (tokenType == "Identifier") {
		output += "$id:";
	}

	if (value != "")
		output += value;
	output += '\n';

	return output;
}
