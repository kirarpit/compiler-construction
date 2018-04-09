#ifndef INCLUDES_OUTPUTSTREAM_H_
#define INCLUDES_OUTPUTSTREAM_H_

#include<iostream>
#include<string>

class OutputStream {
public:
	OutputStream(std::ostream &s) :
			os(s), indentLevel(0), bufferOutput(""), buffer(false) {
	}
	virtual ~OutputStream() {
	}

	OutputStream& operator<<(std::string str);
	OutputStream& operator<<(char ch);
	OutputStream& operator<<(int num);
	void indent();
	void deindent();
	void printWhiteSpaces();
	void startBuffer();
	std::string clearBuffer();

private:
	std::ostream &os;
	int indentLevel;
	std::string bufferOutput;
	bool buffer;
};

#endif /* INCLUDES_OUTPUTSTREAM_H_ */
