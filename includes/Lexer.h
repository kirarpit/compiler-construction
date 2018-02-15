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
	Lexer();
	virtual ~Lexer();

	void scan(InputStream &input, ostream &output);

	bool isSingleByteLiteral(char ch);
	bool isDoubleByteLiteral(string str);
	bool isKeyword(string str);

	Token tokenInit(InputStream &input, string type, char ch);
private:
	string singleByteLiterals;
	vector<string> doubleByteLiterals;
	vector<string> keywords;

	Token tokenizeLiteral(InputStream &input, char ch);
	Token tokenizeNumber(InputStream &input, char ch);
	Token tokenizeKeywordOrID(InputStream &input, char ch);
};

#endif /* SRC_LEXER_H_ */
