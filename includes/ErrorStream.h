#ifndef INCLUDES_ERRORSTREAM_H_
#define INCLUDES_ERRORSTREAM_H_

#include<iostream>

class CompilerState;
class Token;
class Type;

class ErrorStream {
public:
	ErrorStream(std::ostream &s) :
			error(false), es(s), errorCount(0) {
	}

	void reportError(CompilerState &cs, std::string message = "");
	void reportDeclError(CompilerState &cs, Token t);
	void reportTypeError(CompilerState &cs, Token t, Type *type,
			std::string message = "");
	void reportOpTypeError(CompilerState &cs, Token t, Type *type1, Type *type2,
			std::string message = "");
	int getErrorCount();
	void recover(CompilerState &cs, std::string message = "");

	bool error;
private:
	std::ostream &es;
	int errorCount;

	void incrErrorCnt();
	void printErrorEnd();
	void printTokenError(Token t);
	std::string replaceType(CompilerState &cs, std::string message, std::string replace, Type *type);
};

#endif /* INCLUDES_ERRORSTREAM_H_ */
