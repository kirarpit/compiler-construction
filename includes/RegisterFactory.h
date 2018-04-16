#ifndef SRC_REGISTERFACTORY_H_
#define SRC_REGISTERFACTORY_H_

#include<string>

class Register;
class VariableInfo;
class CompilerState;
class Token;
class Node;

class RegisterFactory {
public:
	RegisterFactory();
	virtual ~RegisterFactory();

	Register getAddress(CompilerState &cs, Token t);
	Register loadValue(CompilerState &cs, Token t);
	void storeTemp(CompilerState &cs, Register &r);
	Register loadTemp(CompilerState &cs);
	void freeReg(Register &r);
	void doArithOperation(CompilerState &cs, Register &r1, Register &r2,
			Node *op);

private:
	bool t0;
	bool t1;

	int getFreeReg();
	std::string getInstruction(Node *op);
};

#endif /* SRC_REGISTERFACTORY_H_ */
