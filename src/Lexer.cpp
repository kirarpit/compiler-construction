#include <Lexer.h>
#include<iostream>
#include<InputStream.h>

Lexer::~Lexer() {
}

void Lexer::scan() {

	char ch;
	while (input >> ch) {

		if (ch == '/' && input.peek() == '/') {
			input.read();
			while (input.read() != '\n')
				;
			continue;
		}
	}
}
