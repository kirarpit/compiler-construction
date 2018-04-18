#include<RegisterFactory.h>
#include<CompilerState.h>
#include<SymbolTable.h>
#include<Node.h>
#include<VariableInfo.h>
#include<Token.h>
#include<OutputStream.h>

RegisterFactory::RegisterFactory() {
	t0 = false;
	t1 = false;

	offset = -32768;
}

RegisterFactory::~RegisterFactory() {
}

std::string RegisterFactory::getOpCode(std::string inst, int imm, int sig) {
#define XX(a, b, c, d)	\
	if (a == inst && b == imm && c == sig) {	\
		return d;	\
	}
	OP_CODE_LIST
#undef XX

	return "";
}

Register RegisterFactory::getAddress(CompilerState &cs, Token t) {
	Register r1(0, RT_TEMP);
	VariableInfo *v = cs.lastBlock->getST()->lookup(t);

	Register r2(0, RT_GP, v->offset);
	printInst(cs, "la", r1, r2);

	return r1;
}

Register RegisterFactory::loadValue(CompilerState &cs, Token t) {
	Register r1(0, RT_TEMP);

	if (t.type & TT_ID) {
		VariableInfo *v = cs.lastBlock->getST()->lookup(t);
		Register r2(0, RT_GP, v->offset);
		printInst(cs, "lw", r1, r2);

	} else if (t.type & TT_NUM) {
		cs.os << "\tli $t" << r1.name << " " << t.value << "\n";
	}

	return r1;
}

void RegisterFactory::storeTemp(CompilerState &cs, Register r1) {
	Register r3(0, RT_GP, offset);
	printInst(cs, "sw", r1, r3);

	offset += 4;
}

Register RegisterFactory::loadTemp(CompilerState &cs) {
	Register r2(1, RT_TEMP);
	Register r3(0, RT_GP, (offset - 4));

	printInst(cs, "lw", r2, r3);
	offset -= 4;
	return r2;
}

void RegisterFactory::doArithOperation(CompilerState &cs, Register r1,
		Register r2, Node *op) {

	if (op->getToken().type & TT_TERM_OP) {
		printInst(cs, getOpCode(op->getToken().value, OC_NI, OC_S), r1, r1, r2);
	} else if (op->getToken().type & TT_FACTOR_OP) {
		printInst(cs, getOpCode(op->getToken().value, OC_NI, OC_S), r1, r2);
		printInst(cs, "mflo", r1);
	}

	Register v0(0, RT_EVAL);
	printInst(cs, "move", v0, r1);
}

void RegisterFactory::printInst(CompilerState &cs, std::string opCode,
		Register r1, Register r2, Register r3) {

	cs.os << "\t" << opCode;
	cs.os << " ";
	r1.print(cs);

	if (r2.name != -1) {
		cs.os << " ";
		r2.print(cs);
	}

	if (r3.name != -1) {
		cs.os << " ";
		r3.print(cs);
	}

	cs.os << "\n";
}

void RegisterFactory::freeTempReg(Register r) {
	if (r.type == RT_TEMP) {
		if (r.name == 1) {
			t1 = false;
		} else if (r.name == 0) {
			t0 = false;
		}
	}
}

Register RegisterFactory::getFreeTempReg() {
	int name = -1;
	if (!t0) {
		t0 = true;
		name = 0;
	} else if (!t1) {
		t1 = true;
		name = 1;
	}

	return Register(name, RT_TEMP);
}
