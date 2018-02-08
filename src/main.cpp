#include<iostream>
#include<fstream>
#include<main.h>

using namespace std;

int main(int argc, char **argv) {

	string filename;
	ifstream fileStream;
	if (argc > 1 && argv[1] != NULL) {
		fileStream.open(argv[1], ifstream::in);
		if (fileStream.fail()) {
			cout << "can't open file";
			exit(1);
		}
		filename = argv[1];
	} else {
		filename = "<stdin>";
	}

	InputStream input =
			(filename == "<stdin>") ?
					InputStream(cin, filename) :
					InputStream(fileStream, filename);

	Lexer lex(input, cout);
	lex.scan();

	if (filename != "<stdin>") {
		fileStream.close();
	}
	exit(0);
}

