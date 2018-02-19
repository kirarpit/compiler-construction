#ifndef SRC_LOGGER_H_
#define SRC_LOGGER_H_

#include<stdio.h>
#include<iostream>
#include<string>

class Logger {
public:
	virtual ~Logger();
	static void log(std::string str);
	static bool debug;

private:
	Logger() {
	}
};

#endif /* SRC_LOGGER_H_ */
