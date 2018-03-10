#ifndef SRC_LEXER_H_
#define SRC_LEXER_H_

#include<iostream>
#include<vector>
#include<set>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<sstream>

#include<Token.h>
#include<InputStream.h>
#include<TokenTable.h>
#include<Logger.h>

class Lexer {

public:
	Lexer(InputStream &in);
	virtual ~Lexer();

	Token read();
	Token peek();

	bool isLiteral(std::string str);
	bool isKeyword(std::string str);

	std::string getLiteralType(std::string val);
	Token tokenInit(int type, std::string val);
private:
	InputStream &input;

	std::set<std::string> literals;
	std::set<std::string> keywords;

	Token tokenizeLiteral(std::string val);
	Token tokenizeNumber(std::string val);
	Token tokenizeKeywordOrID(std::string val);

	Token myToken;
	bool peeked;
};

#endif /* SRC_LEXER_H_ */
