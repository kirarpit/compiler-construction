#include <InputStream.h>

InputStream::~InputStream() {
}

InputStream::operator bool() const {
	return !eof_flag;
}

std::string InputStream::read() {
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

		ss.str(std::string());
		ss.clear();
		ss << ch;
		return ss.str();
	} else if (myStream.eof()) { //end of file
		if (!eof_flag) {
			prev_location = location++;
			eof_flag = true;
			return "\0";
		} else
			return "\0";
	} else {
		//error reading
		prev_location = location++;
		eof_flag = true;
		return "\0";
	}
}

InputStream& InputStream::operator>>(std::string &ch) {
	ch = read();
	return *this;
}

std::string InputStream::peek() {
	if (peeked) {
		return myChar;
	}
	if (eof_flag) {
		return "\0";
	}

	myChar = read();
	peeked = true;

	return myChar;
}

void InputStream::setStreamName(std::string name) {
	streamName = name;
}

std::string InputStream::getStreamName() {
	return streamName;
}

int InputStream::getLocation() {
	return (peeked) ? prev_location : location;
}

int InputStream::getLineNumber() {
	if (peeked && peek() == "\n") {
		return lineNum - 1;
	} else
		return lineNum;
}

bool InputStream::is_eof() {
	peek();
	return eof_flag;
}
