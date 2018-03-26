#include<Token.h>
#include<string>
#include<sstream>

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

	output << value;
	return output.str();
}

int Token::getIntVal() {
	std::stringstream s(value);
	int intVal = 0;
	s >> intVal;

	return intVal;
}
