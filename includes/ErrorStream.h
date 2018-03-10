#ifndef INCLUDES_ERRORSTREAM_H_
#define INCLUDES_ERRORSTREAM_H_

#include<iostream>
#include<Logger.h>
#include<CompilerState.h>

class ErrorStream {
public:
	ErrorStream(std::ostream &err) :
			error(false), errorStream(err), errorCount(0) {
	}

	void reportError();
	int getErrorCount();
	void recover(CompilerState &cs);

	bool error;
private:
	std::ostream &errorStream;
	int errorCount;
};

#endif /* INCLUDES_ERRORSTREAM_H_ */
