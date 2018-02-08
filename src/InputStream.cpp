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
