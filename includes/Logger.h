#ifndef SRC_LOGGER_H_
#define SRC_LOGGER_H_

#include<stdio.h>
#include<iostream>
#include<sstream>
#include<string>
#include<Token.h>

inline std::string className(const std::string& prettyFunction) {
	size_t colons = prettyFunction.find("::");
	if (colons == std::string::npos)
		return "::";
	size_t begin = prettyFunction.substr(0, colons).rfind(" ") + 1;
	size_t end = colons - begin;

	return prettyFunction.substr(begin, end);
}

#define __CLASS_NAME__ className(__PRETTY_FUNCTION__)

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
