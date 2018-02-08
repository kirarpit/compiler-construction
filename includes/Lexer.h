#ifndef SRC_LEXER_H_
#define SRC_LEXER_H_

#include <InputStream.h>
#include<string>
#include<iostream>

using namespace std;

class Lexer {

public:
	Lexer(InputStream &is, ostream &os) :
			input(is), output(os) {
	}
	virtual ~Lexer();
	void scan();
	void print(string token, string token_type);
	bool isSingleByteLiteral(char ch);
	bool isDoubleByteLiteral(string str);
	bool isKeyword(string str);

private:
	InputStream &input;
	ostream &output;
};

#endif /* SRC_LEXER_H_ */
