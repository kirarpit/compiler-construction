#include<ByteStream.h>
#include<iostream>

ByteStream::~ByteStream() {
}

char ByteStream::read() {
	if (peeked) {
		peeked = false;
		return myChar;
	}

	char ch;
	if (myStream >>std::noskipws>> ch) {
		return ch;
	} else {
		return '\0';
	}
}

char ByteStream::peek() {
	if (peeked) {
		return myChar;
	}

	myChar = read();
	peeked = true;
	return myChar;
}

bool ByteStream::match(char ch) {
	if (ch == peek()) {
		peeked = false;
		return true;
	} else {
		return false;
	}
}
