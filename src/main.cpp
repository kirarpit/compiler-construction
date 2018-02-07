/*
 * main.cpp
 *
 *  Created on: 07-Feb-2018
 *      Author: Arpit
 */
#include<iostream>
#include<main.h>

using namespace std;

int main() {
	ByteStream s(cin);
	while (s.peek()) {
		if (isspace(s.peek())) {
			if (s.peek() == ' ')
				cout << "space";
			if (s.peek() == 'r')
				cout << "return";
			if (s.peek() == '\f')
				cout << "feed";
			if (s.peek() == '\t')
				cout << "tab";
			if (s.peek() == '\0')
				cout << "null";
			if (s.peek() == '\n')
				cout << "newline";
			if (s.peek() == '\v')
				cout << "verticaltab";
		}
		cout<<endl;
		s.read();
	}

	exit(0);
}

