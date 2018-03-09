#ifndef SRC_LEXER_H_
#define SRC_LEXER_H_

#include<InputStream.h>
#include<Token.h>
#include<vector>

class Lexer {

public:
	Lexer(InputStream &in);
	virtual ~Lexer();

	Token read();
	Token peek();

	bool isSingleByteLiteral(char ch);
	bool isDoubleByteLiteral(std::string str);
	bool isKeyword(std::string str);

	std::string getLiteralType(std::string val);
	Token tokenInit(std::string type, char ch);
private:
	InputStream &input;

	std::string singleByteLiterals;
	std::vector<std::string> doubleByteLiterals;
	std::vector<std::string> keywords;

	Token tokenizeLiteral(char ch);
	Token tokenizeNumber(char ch);
	Token tokenizeKeywordOrID(char ch);

	Token myToken;
	bool peeked;
};

#endif /* SRC_LEXER_H_ */
