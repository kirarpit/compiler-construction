#ifndef INCLUDES_ERRORSTREAM_H_
#define INCLUDES_ERRORSTREAM_H_

#include<iostream>

class CompilerState;
class Token;

class ErrorStream {
public:
	ErrorStream(std::ostream &s) :
			error(false), es(s), errorCount(0) {
	}

	void reportParseError(CompilerState &cs, std::string message = "");
	void reportDeclError(CompilerState &cs, Token t);
	void reportError();
	int getErrorCount();
	void recover(CompilerState &cs, std::string message = "");

	bool error;
private:
	std::ostream &es;
	int errorCount;

	void printErrorEnd();
	void printTokenError(Token t);
};

#endif /* INCLUDES_ERRORSTREAM_H_ */
