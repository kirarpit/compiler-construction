#include<RegisterFactory.h>
#include<CompilerState.h>
#include<SymbolTable.h>
#include<Node.h>
#include<VariableInfo.h>
#include<Register.h>
#include<Token.h>
#include<OutputStream.h>

RegisterFactory::RegisterFactory() {
	t0 = false;
	t1 = false;
}

RegisterFactory::~RegisterFactory() {
}

Register RegisterFactory::getAddress(CompilerState &cs, Token t) {

	int name = getFreeReg();
	VariableInfo *v = cs.lastBlock->getST()->lookup(t);
	cs.os << "\tla t" << name << " " << v->offset << "($gp)\n";

	Register r1(name);
	return r1;
}

Register RegisterFactory::loadValue(CompilerState &cs, Token t) {

	int name = getFreeReg();
	VariableInfo *v = cs.lastBlock->getST()->lookup(t);
	cs.os << "\tlw t" << name << " " << v->offset << "($gp)\n";

	Register r1(name);
	return r1;
}

void RegisterFactory::storeTemp(CompilerState &cs, Register &r) {
	cs.os << "\tmove $t2 $t" << r.name << "\n";
	freeReg(r);
}

Register RegisterFactory::loadTemp(CompilerState &cs) {
	int name = getFreeReg();
	cs.os << "\tmove $t" << name << " $t2\n";

	Register r(name);
	return r;
}

void RegisterFactory::doArithOperation(CompilerState &cs, Register &r1,
		Register &r2, Node *op) {

	cs.os << "\t" << getInstruction(op) << " $t" << r1.name << " $t" << r1.name
			<< " $t" << r2.name << "\n";
	freeReg(r2);

	cs.os << "\tmove $v0 $t" << r1.name << "\n";
}

std::string RegisterFactory::getInstruction(Node *op) {
	std::string result = "";
	if (op->getToken().value == "+") {
		result = "add";
	}
	return result;
}

void RegisterFactory::freeReg(Register &r) {
	if (r.name == 1) {
		t1 = false;
	} else if (r.name == 0) {
		t0 = false;
	}
}

int RegisterFactory::getFreeReg() {
	int name = -1;
	if (!t0) {
		t0 = true;
		name = 0;
	} else if (!t1) {
		t1 = true;
		name = 1;
	}

	return name;
}
