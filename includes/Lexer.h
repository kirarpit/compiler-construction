#ifndef SRC_LEXER_H_
#define SRC_LEXER_H_

#include <InputStream.h>
#include<string>
#include<iostream>

class Lexer {

public:
	Lexer(InputStream &is, std::ostream &os) :
			line(0), location(0), input(is), output(os) {
	}
	virtual ~Lexer();
	void scan();

private:
	int line;
	int location;
	InputStream &input;
	std::ostream &output;
};

#endif /* SRC_LEXER_H_ */
