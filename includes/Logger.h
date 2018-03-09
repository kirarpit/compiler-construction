#ifndef SRC_LOGGER_H_
#define SRC_LOGGER_H_

#include<stdio.h>
#include<iostream>
#include<sstream>
#include<string>
#include<execinfo.h>

class Logger {
public:
	virtual ~Logger();
	static void log(std::string str);
	static void log(std::string str, int i);
	static void logEntry();
	static void logExit();
	static bool debug;

private:
	Logger() {
	}
};

#endif /* SRC_LOGGER_H_ */
