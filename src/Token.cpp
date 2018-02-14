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

	if (tokenType == "Number") {
		output << "$num:";
	} else if (tokenType == "EOF") {
		output << "$EOF";
	} else if (tokenType == "ILLCHR") {
		output << "$illchr:";
	} else if (tokenType == "Identifier") {
		output << "$id:";
	}

	if (value != "")
		output << value;
	output << '\n';

	return output.str();
}
