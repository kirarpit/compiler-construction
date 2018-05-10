#ifndef SRC_REGISTERFACTORY_H_
#define SRC_REGISTERFACTORY_H_

#include<string>
#include<Register.h>

class VariableInfo;
class CompilerState;
class Token;
class Node;
class Type;

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
		XX("==", OC_NI, OC_S, "beq") \
		XX("==", OC_NI, OC_US, "beq") \
		XX("!=", OC_NI, OC_S, "bne") \
		XX("!=", OC_NI, OC_US, "bne") \
		XX("<", OC_NI, OC_S, "blt") \
		XX("<", OC_NI, OC_US, "bltu") \
		XX(">", OC_NI, OC_S, "bgt") \
		XX(">", OC_NI, OC_US, "bgtu") \
		XX("<=", OC_NI, OC_S, "ble") \
		XX("<=", OC_NI, OC_US, "bleu") \
		XX(">=", OC_NI, OC_S, "bge") \
		XX(">=", OC_NI, OC_US, "bgeu") \
		XX("--", OC_NI, OC_S, "sub") \
		XX("--", OC_NI, OC_US, "subu") \
		XX("++", OC_NI, OC_S, "add") \
		XX("++", OC_NI, OC_US, "addu") \


class RegisterFactory {
public:
	RegisterFactory();
	virtual ~RegisterFactory();

	std::string getOpCode(std::string inst, int imm, int sig);

	Register getAddress(CompilerState &cs, Token t);
	Register loadValue(CompilerState &cs, Token t);
	void storeTemp(CompilerState &cs, Register r);
	Register loadTemp(CompilerState &cs, Type *type = NULL);
	Register doArithOperation(CompilerState &cs, Register r1, Register r2,
			Node *op);
	void printInst(CompilerState &cs, std::string opCode, Register r1,
			Register r2 = Register(-1), Register r3 = Register(-1));
	void printLIInst(CompilerState &cs, Register r1, int val);

	int getLabelNo();
	std::string getLabel(int label, int labelNo);
	void printBranchInst(CompilerState &cs, std::string opCode, Register r1,
			Register r2, std::string label);
	void printBranchInst(CompilerState &cs, std::string opCode,
			std::string label);
	void printLabel(CompilerState &cs, std::string label);
	void printTextInst(CompilerState &cs, std::string text);

private:
	int gpOffset;
	int labelCnt;
};

#endif /* SRC_REGISTERFACTORY_H_ */
