#ifndef INCLUDES_INPUTSTREAM_H_
#define INCLUDES_INPUTSTREAM_H_

#include<iostream>
#include<string>
#include<sstream>

class InputStream {

public:
	InputStream(std::istream &s) :
			myStream(s), streamName("<stdin>"), peeked(false), myChar("\0"), location(
					1), prev_location(0), lineNum(1), eof_flag(false) {
	}
	virtual ~InputStream();

	std::string read();
	std::string peek();

	int getLineNumber();
	int getLocation();

	InputStream& operator>>(std::string &ch);
	operator bool() const;
	bool is_eof();

	std::string getStreamName();
	void setStreamName(std::string name);

private:
	std::istream &myStream;
	std::string streamName;
	bool peeked;
	std::string myChar;
	int location;
	int prev_location;
	int lineNum;
	bool eof_flag;
	std::stringstream ss;
};

#endif /* INCLUDES_INPUTSTREAM_H_ */
