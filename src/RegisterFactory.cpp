#include<RegisterFactory.h>
#include<CompilerState.h>
#include<SymbolTable.h>
#include<Node.h>
#include<VariableInfo.h>
#include<Token.h>
#include<OutputStream.h>
#include<Type.h>
#include<Logger.h>
#include<sstream>
#include<CodeGenArgs.h>

RegisterFactory::RegisterFactory() {
	t0 = false;
	t1 = false;

	offset = -32768;
	target = 0;
	label = 0;
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
	Logger::log("Loading Address");

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

		if (v->getAlignment() == 4)
			printInst(cs, "lw", r1, r2);
		else
			printInst(cs, "lbu", r1, r2);

	} else if (t.type & TT_NUM) {
		printLIInst(cs, r1, t.getIntVal());
	}

	return r1;
}

void RegisterFactory::storeTemp(CompilerState &cs, Register r1) {
	Register r3(0, RT_GP, offset);
	printInst(cs, "sw", r1, r3);

	offset += 4;
}

Register RegisterFactory::loadTemp(CompilerState &cs, Type *type) {
	Register r2 = Register(1, RT_TEMP);
	Register r3(0, RT_GP, (offset - 4));

	if (type == NULL || type->getAlignment() == 4)
		printInst(cs, "lw", r2, r3);
	else
		printInst(cs, "lbu", r2, r3);

	offset -= 4;
	return r2;
}

Register RegisterFactory::doArithOperation(CompilerState &cs, Register r2,
		Register r1, Node *root) {

	Node *op = root->getChild(1);
	Type *t = root->getType();

	int oc_s = -1;
	if (t->typeName == TP_SIGNED) {
		oc_s = OC_S;
	} else {
		oc_s = OC_US;
	}

	if (op->getToken().type & TT_TERM_OP) {
		printInst(cs, getOpCode(op->getToken().value, OC_NI, OC_US), r1, r2,
				r1);
	} else if (op->getToken().type & TT_FACTOR_OP) {
		printInst(cs, getOpCode(op->getToken().value, OC_NI, oc_s), r2, r1);
		printInst(cs, "mflo", r1);
	} else if ((op->getToken().type & TT_REL_OP)
			|| (op->getToken().type & TT_EQ_OP)) {

		printEQInst(cs, getOpCode(op->getToken().value, OC_NI, OC_US), r2, r1);
		printLIInst(cs, r1, 0);

		cs.os << "\tb ";
		printSkipTarget(cs);
		cs.os << "\n";

		printTargetLabel(cs);
		printLIInst(cs, r1, 1);

		printSkipTargetLabel(cs);

		target++;
	}

	return r1;
}

void RegisterFactory::printEQInst(CompilerState &cs, std::string opCode,
		Register r1, Register r2) {
	cs.os << "\t" << opCode;
	cs.os << " ";

	r1.print(cs);
	cs.os << " ";
	r2.print(cs);
	cs.os << " ";
	printTarget(cs);
	cs.os << "\n";
}

void RegisterFactory::printTarget(CompilerState &cs) {
	cs.os << "target" << target;
}

void RegisterFactory::printTargetLabel(CompilerState &cs) {
	cs.os << "target" << target << ":\n";
}

void RegisterFactory::printSkipTarget(CompilerState &cs) {
	cs.os << "skiptarget" << target;
}

void RegisterFactory::printSkipTargetLabel(CompilerState &cs) {
	cs.os << "skiptarget" << target << ":\n";
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

void RegisterFactory::printLIInst(CompilerState &cs, Register r1, int val) {
	cs.os << "\tli $t" << r1.name << " " << val << "\n";
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

int RegisterFactory::getLabelNo() {
	label++;
	return label;
}
std::string RegisterFactory::getLabel(int label, int labelNo) {
	std::ostringstream oss;

	if (label == FalseL)
		oss << "FalseL";
	else if (label == TrueL)
		oss << "TrueL";

	oss << labelNo;
	return oss.str();
}

void RegisterFactory::printBranchInst(CompilerState &cs, std::string opCode,
		Register r1, Register r2, std::string label) {

	cs.os << "\t" << opCode;
	cs.os << " ";
	r1.print(cs);
	cs.os << " ";
	r2.print(cs);
	cs.os << " " << label << "\n";
}

void RegisterFactory::printBranchInst(CompilerState &cs, std::string opCode,
		std::string label) {
	cs.os << "\t" << opCode;
	cs.os << " ";
	cs.os << label;
	cs.os << "\n";
}

void RegisterFactory::printLabel(CompilerState &cs, std::string label) {
	cs.os << label << ":\n";
}
