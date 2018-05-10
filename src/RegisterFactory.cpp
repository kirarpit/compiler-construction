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
	gpOffset = -32768;
	labelCnt = 0;
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
	Register r3(0, RT_GP, gpOffset);
	printInst(cs, "sw", r1, r3);

	gpOffset += 4;
}

Register RegisterFactory::loadTemp(CompilerState &cs, Type *type) {
	Register r2 = Register(1, RT_TEMP);
	Register r3(0, RT_GP, (gpOffset - 4));

	if (type == NULL || type->getAlignment() == 4)
		printInst(cs, "lw", r2, r3);
	else
		printInst(cs, "lbu", r2, r3);

	gpOffset -= 4;
	return r2;
}

Register RegisterFactory::doArithOperation(CompilerState &cs, Register r2,
		Register r1, Node *root) {

	Node *op = root->getChild(1);
	Type *t = root->getType();

	int ocSign = -1;
	if (t->typeName == TP_SIGNED) {
		ocSign = OC_S;
	} else if (t->typeName == TP_UNSIGNED) {
		ocSign = OC_US;
	}

	if (op->getToken().type & TT_TERM_OP) {
		printInst(cs, getOpCode(op->getToken().value, OC_NI, OC_US), r1, r2,
				r1);
	} else if (op->getToken().type & TT_FACTOR_OP) {
		printInst(cs, getOpCode(op->getToken().value, OC_NI, ocSign), r2, r1);
		printInst(cs, "mflo", r1);
	} else if ((op->getToken().type & TT_REL_OP)
			|| (op->getToken().type & TT_EQ_OP)) {

		if (root->getChild(0)->getType()->typeName == TP_SIGNED)
			ocSign = OC_S;
		else
			ocSign = OC_US;

		int labelNo = cs.rf.getLabelNo();
		std::string tLabel = cs.rf.getLabel(TrueL, labelNo);
		std::string fLabel = cs.rf.getLabel(FalseL, labelNo);

		printBranchInst(cs, getOpCode(op->getToken().value, OC_NI, ocSign), r2,
				r1, tLabel);
		printLIInst(cs, r1, 0);

		cs.rf.printBranchInst(cs, "b", fLabel);
		cs.rf.printLabel(cs, tLabel);
		printLIInst(cs, r1, 1);

		cs.rf.printLabel(cs, fLabel);
	}

	return r1;
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
	cs.os << "\tli";
	cs.os << " ";
	r1.print(cs);

	cs.os << " " << val << "\n";
}

int RegisterFactory::getLabelNo() {
	labelCnt++;
	return labelCnt;
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

void RegisterFactory::printTextInst(CompilerState &cs, std::string text) {
	cs.os << "\t" << text << "\n";
}
