#ifndef SRC_REGISTERFACTORY_H_
#define SRC_REGISTERFACTORY_H_

#include<string>
#include<Register.h>

class VariableInfo;
class CompilerState;
class Token;
class Node;

enum {
	OC_NI, OC_I
};

enum {
	OC_US, OC_S
};

#define OP_CODE_LIST \
		XX("+", OC_NI, OC_S, "add") \
		XX("+", OC_I, OC_S, "addi") \
		XX("+", OC_I, OC_US, "addiu") \
		XX("+", OC_NI, OC_US, "addu") \
		XX("-", OC_NI, OC_S, "sub") \
		XX("-", OC_NI, OC_US, "subu") \
		XX("*", OC_NI, OC_S, "mult") \
		XX("*", OC_NI, OC_US, "multu") \
		XX("/", OC_NI, OC_S, "div") \
		XX("/", OC_NI, OC_US, "divu") \


class RegisterFactory {
public:
	RegisterFactory();
	virtual ~RegisterFactory();

	std::string getOpCode(std::string inst, int imm, int sig);

	Register getAddress(CompilerState &cs, Token t);
	Register loadValue(CompilerState &cs, Token t);
	void storeTemp(CompilerState &cs, Register r);
	Register loadTemp(CompilerState &cs);
	void doArithOperation(CompilerState &cs, Register r1, Register r2,
			Node *op);

private:
	bool t0;
	bool t1;

	Register getFreeTempReg();
	void freeTempReg(Register r);
	void printInst(CompilerState &cs, std::string opCode, Register r1,
			Register r2 = Register(-1), Register r3 = Register(-1));

	int offset;
};

#endif /* SRC_REGISTERFACTORY_H_ */
