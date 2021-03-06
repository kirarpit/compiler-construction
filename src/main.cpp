#include<main.h>

int main(int argc, char **argv) {
	std::string filename;
	std::ifstream fileStream;

	if (argc > 1 && argv[1] != NULL) {
		fileStream.open(argv[1], std::ifstream::in);
		if (fileStream.fail()) {
			exit(1);
		}
		filename = argv[1];
	} else {
		filename = "<stdin>";
	}

	InputStream input((filename == "<stdin>") ? std::cin : fileStream);
	input.setStreamName(filename);

	OutputStream output(std::cout);
	Lexer lex = Lexer(input);
	ErrorStream error(std::cerr);
	TypeFactory typeFactory;
	RegisterFactory regFactory;

	CompilerState cs(input, output, error, lex, typeFactory, regFactory);

	NodeSpike5::compile(cs);
	exit(cs.es.getErrorCount());
}

