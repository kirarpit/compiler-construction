#include "Logger.h"

bool Logger::debug = false;

Logger::~Logger() {
}

void Logger::log(std::string str) {
	if (debug) {
		std::cout << str << '\n';
	}
}

void Logger::log(std::string str, int i) {
	if (debug) {
		std::ostringstream os;
		os << i;
		os.str();
		str.replace(str.find("%d"), std::string("%d").length(), os.str());
		std::cout << str << '\n';
	}
}
