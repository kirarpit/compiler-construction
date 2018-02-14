#ifndef SRC_TOKEN_H_
#define SRC_TOKEN_H_

#include<string>

class Token {
public:
	Token();
	Token(std::string filename, int line, int pos, std::string tokenType,
			std::string val) :
			filename(filename), line(line), position(pos), tokenType(tokenType), value(
					val) {
	}
	virtual ~Token();

	std::string print();

private:
	std::string filename;
	int line;
	int position;
	std::string tokenType;
	std::string value;
};

#endif /* SRC_TOKEN_H_ */
