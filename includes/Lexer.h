#ifndef SRC_LEXER_H_
#define SRC_LEXER_H_

#include<iostream>
#include<vector>
#include<map>z
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<sstream>

#include<Token.h>

class InputStream;
class TokenTable;

class Lexer {

public:
	Lexer(InputStream &in);
	virtual ~Lexer();

	Token read();
	Token peek();

	bool isLiteral(std::string str);
	bool isKeyword(std::string str);

	Token tokenInit(int type, std::string val);

private:
	InputStream &input;

	std::map<std::string, int> literals;
	std::map<std::string, int> keywords;

	Token tokenizeLiteral(std::string val);
	Token tokenizeNumber(std::string val);
	Token tokenizeKeywordOrID(std::string val);

	Token myToken;
	bool peeked;
};

#endif /* SRC_LEXER_H_ */
