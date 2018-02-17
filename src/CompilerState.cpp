#include"CompilerState.h"

int CompilerState::reportError() {
	//output in std error expected node but found token
	error = true;
	return ++errorCount;
}
