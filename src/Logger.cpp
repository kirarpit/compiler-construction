#include<Logger.h>
#include<Node.h>

bool Logger::debug = false;

Logger::~Logger() {
}

void Logger::log(std::string str, int i) {
	if (debug) {
		if (str.find("%d") != std::string::npos) {
			std::ostringstream os;
			os << i;
			os.str();
			str.replace(str.find("%d"), std::string("%d").length(), os.str());
		}
		std::cout << str << '\n';
	}
}

void Logger::logConst(std::string str) {
	log(str + " Constructor Called");
}

void Logger::logDest(std::string str) {
	log(str + " Destructor Called");
}

void Logger::logTerminal(Token tkn) {
	log("Consumed Terminal. Token:" + tkn.stringify());
}

void Logger::logParseEntry(std::string name, Token tkn) {
//	log("ParseEntry " + name + " @ " + tkn.stringify());
}

void Logger::logParseExit(std::string name, Token tkn) {
//	log("ParseExit " + name + " @ " + tkn.stringify());
}

void Logger::logWalkEntry(std::string name, Node *node) {
	log(
			"WalkEntry " + name + ", Token:" + node->getToken().stringify()
					+ ", Size: %d", node->getSize());
}

void Logger::logWalkExit(std::string name, Node *node) {
	log(
			"WalkExit " + name + ", Token:" + node->getToken().stringify()
					+ ", Size: %d", node->getSize());
}

void Logger::logGenCodeEntry(std::string name, Node *node) {
	log("GenCode Entry " + name);
}

void Logger::logGenCodeExit(std::string name, Node *node) {
	log("GenCode Exit " + name);
}
