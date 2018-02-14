#ifndef INCLUDES_INPUTSTREAM_H_
#define INCLUDES_INPUTSTREAM_H_

#include<iostream>
#include<string>

class InputStream {

public:
	InputStream(std::istream &s) :
			myStream(s), streamName("<stdin>"), peeked(false), myChar('\0'), location(
					1), prev_location(0), lineNum(1), eof_flag(false) {
	}
	virtual ~InputStream();

	char read();
	char peek();
	bool match(char ch);

	int getLineNumber();
	int getLocation();

	InputStream& operator>>(char &ch);
	operator bool() const;
	bool is_eof();

	std::string getStreamName();
	void setStreamName(std::string name);

private:
	std::istream &myStream;
	std::string streamName;
	bool peeked;
	char myChar;
	int location;
	int prev_location;
	int lineNum;
	bool eof_flag;
};

#endif /* INCLUDES_INPUTSTREAM_H_ */
