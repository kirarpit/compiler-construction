#ifndef INCLUDES_ERRORSTREAM_H_
#define INCLUDES_ERRORSTREAM_H_

#include<iostream>

class CompilerState;

class ErrorStream {
public:
	ErrorStream(std::ostream &s) :
			error(false), es(s), errorCount(0) {
	}

	void reportParseError(CompilerState &cs);
	void reportError();
	int getErrorCount();
	void recover(CompilerState &cs);

	bool error;
private:
	std::ostream &es;
	int errorCount;
};

#endif /* INCLUDES_ERRORSTREAM_H_ */
