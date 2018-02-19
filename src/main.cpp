#include<iostream>
#include<fstream>
#include<cstdlib>

#include<main.h>

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

	InputStream input((filename == "<stdin>") ? cin : fileStream);
	input.setStreamName(filename);

	OutputStream &output = cout;
	Lexer lex = Lexer(input);
	CompilerState cs(input, output, lex);

	NodeSpike2::parse(cs);

	exit(cs.getErrorCount());
}

