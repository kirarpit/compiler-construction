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
			prev_location = location;
			location = 1;
		} else {
			prev_location = location++;
		}
		return ch;
	} else if (!eof_flag) {
		prev_location = location++;
		eof_flag = true;
		return '\0';
	} else
		return '\0';
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
	return (peeked) ? prev_location : location;
}

int InputStream::getLineNumber() {
	if (peeked && peek() == '\n') {
		return lineNum - 1;
	} else
		return lineNum;
}

bool InputStream::is_eof() {
	return eof_flag;
}
