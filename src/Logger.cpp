#include "Logger.h"

bool Logger::debug = false;

Logger::~Logger() {
}

void Logger::log(std::string str) {
	if (debug) {
		std::cout << str;
	}
}
