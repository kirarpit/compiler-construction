#ifndef SRC_LEXER_H_
#define SRC_LEXER_H_

#include<InputStream.h>
#include<Token.h>
#include<string>
#include<iostream>
#include<vector>

using namespace std;

class Lexer {

public:
	Lexer(InputStream &in);
	virtual ~Lexer();

	Token read();
	Token peek();
	void recover();

	bool isSingleByteLiteral(char ch);
	bool isDoubleByteLiteral(string str);
	bool isKeyword(string str);

	string getLiteralType(string val);
	Token tokenInit(string type, char ch);
private:
	InputStream &input;

	string singleByteLiterals;
	vector<string> doubleByteLiterals;
	vector<string> keywords;

	Token tokenizeLiteral(char ch);
	Token tokenizeNumber(char ch);
	Token tokenizeKeywordOrID(char ch);

	Token myToken;
	bool peeked;
};

#endif /* SRC_LEXER_H_ */
