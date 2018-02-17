#ifndef SRC_TOKEN_H_
#define SRC_TOKEN_H_

#include<string>
using namespace std;

class Token {
public:
	Token() :
			line(), position() {
	}

	Token(string value) :
			line(), position(), value(value) {
	}

	Token(string filename, int line, int pos, string tokenType, string val) :
			filename(filename), line(line), position(pos), type(tokenType), value(
					val) {
	}
	virtual ~Token();
	string print();

	string filename;
	int line;
	int position;
	string type;
	string subType;
	string value;
};

#endif /* SRC_TOKEN_H_ */
