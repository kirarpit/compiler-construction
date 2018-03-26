#include<TerminalNode.h>
#include<Logger.h>
#include<CompilerState.h>
#include<VariableInfo.h>
#include<SymbolTable.h>
#include<TypeInfo.h>
#include<OutputStream.h>

TerminalNode::TerminalNode(Token tkn) :
		token(tkn) {
	isTerminal = true;

	if ((tkn.type & TT_NUM)) {
		isConstant = true;
	}

	Logger::logTerminal(tkn);
}

TerminalNode::~TerminalNode() {
}

void TerminalNode::print(CompilerState &cs) {
	cs.os << token.value;
}

void TerminalNode::walk(CompilerState &cs) {
	if (token.type == TT_ID)
		type = cs.lastBlock->getST()->lookup(token)->type;
	else if (token.type == TT_NUM)
		type = new TypeInfo(TP_SIGNED, 0);
}

Token TerminalNode::getToken() {
	return token;
}
