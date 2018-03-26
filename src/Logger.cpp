#include<Logger.h>
#include<Node.h>

bool Logger::debug = true;

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
void Logger::logTerminal(Token tkn) {
	log("Consumed Terminal. Token:" + tkn.print());
}

void Logger::logParseEntry(std::string name, Token tkn) {
//	log("ParseEntry " + name + " @ " + tkn.print());
}

void Logger::logParseExit(std::string name, Token tkn) {
//	log("ParseExit " + name + " @ " + tkn.print());
}

void Logger::logWalkEntry(std::string name, Node *node) {
	log("WalkEntry " + name + ", Token:" + node->getToken().print());
}

void Logger::logWalkExit(std::string name, Node *node) {
	log("WalkExit " + name);
}
