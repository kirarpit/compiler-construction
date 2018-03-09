#ifndef SRC_TOKEN_H_
#define SRC_TOKEN_H_

#include<string>
#include<sstream>

class Token {
public:
	Token() :
			line(), position() {
	}

	Token(std::string filename, int line, int pos, std::string tokenType,
			std::string val) :
			filename(filename), line(line), position(pos), type(tokenType), value(
					val) {
	}
	virtual ~Token();
	std::string print();

	std::string filename;
	int line;
	int position;
	std::string type;
	std::string subType;
	std::string value;
};

#endif /* SRC_TOKEN_H_ */
