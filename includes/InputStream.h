#ifndef INCLUDES_INPUTSTREAM_H_
#define INCLUDES_INPUTSTREAM_H_

#include<iostream>
#include<string>

class InputStream {

public:
	InputStream(std::istream &s, std::string str) :
			myStream(s), name(str), peeked(false), myChar('\0') {
	}
	virtual ~InputStream();
	char read();
	char operator>>(char &ch);
	char peek();
	bool match(char ch);

private:
	std::istream &myStream;
	std::string name;
	bool peeked;
	char myChar;
};

#endif /* INCLUDES_INPUTSTREAM_H_ */
