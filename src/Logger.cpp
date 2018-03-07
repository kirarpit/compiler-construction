#include "Logger.h"

bool Logger::debug = true;

Logger::~Logger() {
}

void Logger::log(std::string str) {
	if (debug) {
		std::cout << str;
	}
}
