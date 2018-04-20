#include<TerminalNode.h>
#include<Logger.h>
#include<CompilerState.h>
#include<VariableInfo.h>
#include<SymbolTable.h>
#include<OutputStream.h>
#include<Type.h>
#include<TypeFactory.h>
#include<CodeGenArgs.h>
#include<Register.h>
#include<RegisterFactory.h>

TerminalNode::TerminalNode(Token tkn) :
		token(tkn) {
	isTerminal = true;

	if (tkn.type & TT_NUM) {
		isConstant = true;
	}
	if (tkn.type & TT_ID) {
		isAssignable = true;
	}

	Logger::logTerminal(tkn);
}

TerminalNode::~TerminalNode() {
}

void TerminalNode::print(CompilerState &cs) {
	if (type)
		type->shortPrint(cs);
	cs.os << token.value;
}

void TerminalNode::walk(CompilerState &cs) {
	Logger::logWalkEntry(__CLASS_NAME__, this);

	if (token.type == TT_ID)
		type = cs.lastBlock->getST()->lookup(token)->type;
	else if (token.type == TT_NUM)
		type = cs.tf.getPrimType(TP_SIGNED);

	Logger::logWalkExit(__CLASS_NAME__, this);
}

Register TerminalNode::genCode(CompilerState &cs, CodeGenArgs cg) {
	Logger::logGenCodeEntry(__CLASS_NAME__, this);

	Register r1(-1);
	if ((token.type & TT_ID) || (token.type & TT_NUM)) {
		if (cg.develop == GET_ADDRESS) {
			r1 = cs.rf.getAddress(cs, token);
		} else if (cg.develop == GET_VALUE) {
			r1 = cs.rf.loadValue(cs, token);
		}
	}

	return r1;

	Logger::logGenCodeExit(__CLASS_NAME__, this);
}

Token TerminalNode::getToken() {
	return token;
}
