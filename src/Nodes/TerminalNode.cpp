#include<TerminalNode.h>
#include<Logger.h>
#include<CompilerState.h>
#include<VariableInfo.h>
#include<SymbolTable.h>

TerminalNode::TerminalNode(Token tkn) :
		token(tkn) {
	Logger::logTerminal(tkn);
}

TerminalNode::~TerminalNode() {
}

void TerminalNode::print(CompilerState &cs) {
	cs.os << token.value;
}

void TerminalNode::walk(CompilerState &cs) {
	VariableInfo *var = cs.lastBlock->getST()->lookup(token);
	if (var)
		type = var->type;
	else if (token.type == TT_NUM)
		type = new TypeInfo(TP_SIGNED, new TerminalNode(token));
}
