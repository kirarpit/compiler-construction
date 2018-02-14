#include<iostream>
#include<fstream>
#include<main.h>
#include<cstdlib>

using namespace std;

int main(int argc, char **argv) {

	string filename;
	ifstream fileStream;
	if (argc > 1 && argv[1] != NULL) {
		fileStream.open(argv[1], ifstream::in);
		if (fileStream.fail()) {
			exit(1);
		}
		filename = argv[1];
	} else {
		filename = "<stdin>";
	}

	InputStream input =
			(filename == "<stdin>") ?
					InputStream(cin) : InputStream(fileStream); //any other better way to do this?

	input.setStreamName(filename);

	Lexer lex = Lexer();
	lex.scan(input, cout);

	if (filename != "<stdin>") {
		fileStream.close();
	}
	exit(0);
}

