#ifndef SRC_LOGGER_H_
#define SRC_LOGGER_H_

#include<stdio.h>
#include<iostream>
#include<sstream>
#include<string>
#include<execinfo.h>
#include<Token.h>

class Logger {
public:
	virtual ~Logger();
	static void log(std::string str);
	static void log(std::string str, int i);
	static void logConsTerm(Token tkn);
	static void logNodeEntry(std::string name, Token tkn);
	static void logNodeExit(std::string name, Token tkn);

	static bool debug;

private:
	Logger() {
	}
};

#endif /* SRC_LOGGER_H_ */
