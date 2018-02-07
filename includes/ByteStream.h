#ifndef INCLUDES_BYTESTREAM_H_
#define INCLUDES_BYTESTREAM_H_

#include<iostream>

class ByteStream {

public:
	ByteStream(std::istream &s) :
			myStream(s), peeked(false), myChar('\0') {
	}
	virtual ~ByteStream();
	char read();
	char peek();
	bool match(char ch);

private:
	std::istream &myStream;
	bool peeked;
	char myChar;
};

#endif /* INCLUDES_BYTESTREAM_H_ */
