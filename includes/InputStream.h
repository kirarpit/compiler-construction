#ifndef INCLUDES_INPUTSTREAM_H_
#define INCLUDES_INPUTSTREAM_H_

#include<iostream>
#include<string>

class InputStream {

public:
	InputStream(std::istream &s, std::string str) :
			myStream(s), fileName(str), peeked(false), myChar('\0'), location(
					1), prev_location(0), lineNum(1), eof_flag(false) {
	}
	virtual ~InputStream();
	char read();
	char operator>>(char &ch);
	char peek();
	bool match(char ch);
	std::string getFileName();
	int getLineNumber();
	int getLocation();
	bool is_eof();

private:
	std::istream &myStream;
	std::string fileName;
	bool peeked;
	char myChar;
	int location;
	int prev_location;
	int lineNum;
	bool eof_flag;
};

#endif /* INCLUDES_INPUTSTREAM_H_ */
