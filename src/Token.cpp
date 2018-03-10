#include "Token.h"

Token::~Token() {
}

std::string Token::print() {
	std::ostringstream output;

	output << filename << ':' << line << ':' << position << ':';

	if (type == TT_NUM) {
		output << "$num:";
	} else if (type == TT_EOF) {
		output << "$EOF";
	} else if (type == TT_ILLCHR) {
		output << "$illchr:";
	} else if (type == TT_ID) {
		output << "$id:";
	}

	return output.str();
}
