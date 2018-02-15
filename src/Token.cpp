#include "Token.h"
#include<sstream>

Token::~Token() {
}

std::string Token::print() {
	std::ostringstream output;

	output << filename;
	output << ':';
	output << line;
	output << ':';
	output << position;
	output << ':';

	if (type == "Number") {
		output << "$num:";
	} else if (type == "EOF") {
		output << "$EOF";
	} else if (type == "ILLCHR") {
		output << "$illchr:";
	} else if (type == "Identifier") {
		output << "$id:";
	}

	if (value != "")
		output << value;
	output << '\n';

	return output.str();
}
