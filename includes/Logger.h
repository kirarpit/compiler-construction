#ifndef SRC_LOGGER_H_
#define SRC_LOGGER_H_

#include<stdio.h>
#include<iostream>
#include<sstream>
#include<string>
#include<Token.h>

class Node;

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

	static void logConst(std::string str);
	static void logDest(std::string str);

	static void logTerminal(Token tkn);

	static void logParseEntry(std::string name, Token tkn);
	static void logParseExit(std::string name, Token tkn);

	static void logWalkEntry(std::string name, Node *node);
	static void logWalkExit(std::string name, Node *node);

	static bool debug;

private:
	Logger() {
	}
};

#endif /* SRC_LOGGER_H_ */
