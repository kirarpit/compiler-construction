#include <InputStream.h>
#include<iostream>

InputStream::~InputStream() {
}

char InputStream::read() {
	if (peeked) {
		peeked = false;
		return myChar;
	}

	char ch;
	if (myStream >> std::noskipws >> ch) {
		if (ch == '\n') {
			lineNum++;
			location = 1;
		} else {
			location++;
		}
		return ch;
	} else {
		return '\0';
	}
}

char InputStream::operator>>(char &ch) {
	ch = read();
	return ch;
}

char InputStream::peek() {
	if (peeked) {
		return myChar;
	}

	myChar = read();
	peeked = true;
	return myChar;
}

bool InputStream::match(char ch) {
	if (ch == peek()) {
		peeked = false;
		return true;
	} else {
		return false;
	}
}

std::string InputStream::getFileName() {
	return fileName;
}

int InputStream::getLocation() {
	return (peeked) ? (location - 1) : location;
}

int InputStream::getLineNumber() {
	return lineNum;
}
