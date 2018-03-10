#ifndef SRC_TOKEN_H_
#define SRC_TOKEN_H_

#include<string>
#include<sstream>
#include<TokenTable.h>

class Token {
public:
	Token() :
			line(), position(), type(-1) {
	}

	Token(std::string filename, int line, int pos, int tokenType,
			std::string val) :
			filename(filename), line(line), position(pos), type(tokenType), value(
					val) {
	}
	virtual ~Token();
	std::string print();

	std::string filename;
	int line;
	int position;
	int type;
	std::string subType;
	std::string value;
};

#endif /* SRC_TOKEN_H_ */
