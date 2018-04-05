#ifndef SRC_TOKEN_H_
#define SRC_TOKEN_H_

#include<string>
#include<sstream>
#include<TokenTable.h>

class Token {
public:
	Token() :
			line(-1), position(-1), type(-1) {
	}
	Token(int tokenType, std::string val) :
			line(-1), position(-1), type(tokenType), value(val) {
	}
	Token(std::string filename, int line, int pos, int tokenType,
			std::string val) :
			filename(filename), line(line), position(pos), type(tokenType), value(
					val) {
	}
	virtual ~Token();

	bool operator<(const Token &t) const;

	std::string print();
	int getIntVal();

	std::string filename;
	int line;
	int position;
	int type;
	std::string value;
};

#endif /* SRC_TOKEN_H_ */
