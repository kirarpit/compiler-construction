#include<TerminalNode.h>
#include<Logger.h>
#include<CompilerState.h>
#include<VariableInfo.h>
#include<SymbolTable.h>
#include<OutputStream.h>
#include<Type.h>
#include<TypeFactory.h>

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
	if (type)
		type->shortPrint(cs);
	cs.os << token.value;
}

void TerminalNode::walk(CompilerState &cs) {
	Logger::logWalkEntry(__CLASS_NAME__, this);
	Logger::log("Terminal Node Token value:" + token.value);

	if (token.type == TT_ID)
		type = cs.lastBlock->getST()->lookup(token)->type;
	else if (token.type == TT_NUM)
		type = TypeFactory::getPrimType(TP_SIGNED);

	Logger::logWalkExit(__CLASS_NAME__, this);
}

Token TerminalNode::getToken() {
	return token;
}
