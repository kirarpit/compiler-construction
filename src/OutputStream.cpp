#include "OutputStream.h"

void OutputStream::indent() {
	indentLevel++;
}

void OutputStream::deindent() {
	indentLevel--;
}

void OutputStream::printWhiteSpaces() {
	if (indentLevel > 0) {
		os << std::string(2 * indentLevel, ' ');
	}
}

OutputStream& OutputStream::operator<<(std::string str) {
	if (buffer) {
		bufferOutput += str;
	} else
		os << str;
	return *this;
}

OutputStream& OutputStream::operator<<(char ch) {
	if (buffer) {
		std::string str;
		str.push_back(ch);
		bufferOutput += str;
	} else
		os << ch;
	return *this;
}

OutputStream& OutputStream::operator<<(int num) {
	if (buffer) {
		std::string str;
		str.push_back(num);
		bufferOutput += str;
	} else
		os << num;
	return *this;
}

void OutputStream::startBuffer() {
	buffer = true;
	bufferOutput = "";
}

std::string OutputStream::clearBuffer() {
	buffer = false;
	return bufferOutput;
}
