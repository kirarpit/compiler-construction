#include<NonTerminalNode.h>
#include<CompilerState.h>
#include<OutputStream.h>
#include<Logger.h>
#include<typeinfo>
#include<RegisterFactory.h>
#include<Register.h>

NonTerminalNode::NonTerminalNode() {
}

NonTerminalNode::~NonTerminalNode() {
	for (unsigned int i = 0; i < children.size(); i++) {
		delete children[i];
	}
}

void NonTerminalNode::addNode(Node *node) {
	children.push_back(node);
}

void NonTerminalNode::genCodeAll(CompilerState &cs, CodeGenArgs cg) {
	for (unsigned int i = 0; i < children.size(); i++) {
		children[i]->genCode(cs, cg);
	}
}

Register NonTerminalNode::genCodeArithmetic(CompilerState &cs, CodeGenArgs cg) {
	Register r1(-1);

	if (children.size() == 3) {
		r1 = children[0]->genCode(cs, cg);
		cs.rf.storeTemp(cs, r1);

		r1 = children[2]->genCode(cs, cg);
		Register r2 = cs.rf.loadTemp(cs);

		r1 = cs.rf.doArithOperation(cs, r2, r1, this);
	}

	return r1;
}

Register NonTerminalNode::genFallThroughCode(CompilerState &cs,
		CodeGenArgs cg) {
	Register r1(-1);
	int labelNo = cs.rf.getLabelNo();

	std::string opCode = "";
	int immVal = 0;
	if (cg.fall == FALL_TRUE) {
		opCode = "be";
		immVal = 1;
	} else if (cg.fall == FALL_FALSE) {
		opCode = "bne";
		immVal = 0;
	}

	std::string label = cs.rf.getLabel(cg.l1, labelNo);

	r1 = children[0]->genCode(cs, cg);
	cs.rf.printBranchInst(cs, opCode, r1, Register(0, RT_ZERO), label);
	r1 = children[2]->genCode(cs, cg);
	cs.rf.printBranchInst(cs, opCode, r1, Register(0, RT_ZERO), label);

	cs.rf.printLIInst(cs, r1, immVal);
	cs.rf.printBranchInst(cs, "b", cs.rf.getLabel(cg.l2, labelNo));

	cs.rf.printLabel(cs, label);
	cs.rf.printLIInst(cs, r1, !immVal);

	cs.rf.printLabel(cs, cs.rf.getLabel(cg.l2, labelNo));

	return r1;
}

void NonTerminalNode::smartWalk(CompilerState &cs) {
	walkAllChildren(cs);
	typeProp(cs);
	constFold(cs);
}

void NonTerminalNode::walkAllChildren(CompilerState &cs) {
	for (unsigned int i = 0; i < children.size(); i++) {
		children[i]->walk(cs);

		if (children[i]->isEmpty()) {
			deleteChild(i);
			i--;
		} else {
			Node *temp = reduceBranch(children[i]);
			if (temp)
				children[i] = temp;
		}
	}
}

Node* NonTerminalNode::reduceBranch(Node *node) {
	if (node->isRemovable()) {
		Node *temp = node;
		node = temp->getChild(0);
		temp->clearChildren();
		delete temp;

		return node;
	}

	return NULL;
}

void NonTerminalNode::typeProp(CompilerState &cs) {
	Logger::log("Type Propagating");

	if (children.size() == 1) {
		type = children[0]->getType();

	} else if (children.size() == 3) {
		if (children[0]->getType() && children[2]->getType())
			type = Type::getOperatorType(cs, children[1]->getToken(),
					children[0]->getType(), children[2]->getType());
	}

	Logger::log("Exit Type Propagating");
}

void NonTerminalNode::constFold(CompilerState &cs) {
	Logger::log("Constant Folding");

	if (children.size() == 3) {
		if (children[0]->isConstant && children[2]->isConstant) {
			Node* terminalNode = Type::constantFold(cs, children[1]->getToken(),
					children[0]->getToken(), children[2]->getToken());

			if (terminalNode) {
				terminalNode->setType(type);
				deleteChildren();
				addNode(terminalNode);
			}
		}
	}

	Logger::log("Exit Constant Folding");
}

Node* NonTerminalNode::getChild(int index) {
	return children[index];
}

int NonTerminalNode::getSize() {
	return children.size();
}

void NonTerminalNode::clearChildren() {
	children.clear();
}

void NonTerminalNode::deleteChildren() {
	for (unsigned int i = 0; i < children.size(); i++) {
		delete children[i];
	}
	clearChildren();
}

void NonTerminalNode::deleteChild(int i) {
	delete children[i];
	children.erase(children.begin() + i);
}

void NonTerminalNode::clearChild(int i) {
	children.erase(children.begin() + i);
}

bool NonTerminalNode::isRemovable() {
	if (children.size() == 1) {
		return true;
	}
	return false;
}

bool NonTerminalNode::isEmpty() {
	if (children.size() == 0) {
		return true;
	}
	return false;
}

bool NonTerminalNode::findPostfixExpr() {
	if (getName() == "15NodePostfixExpr")
		return true;
	if (children.size() != 1)
		return false;

	return children[0]->findPostfixExpr();
}

std::string NonTerminalNode::getName() {
	return std::string("") + typeid(*this).name();
}

void NonTerminalNode::printAllChildren(CompilerState &cs) {
	for (unsigned int i = 0; i < children.size(); i++) {
		children[i]->print(cs);
	}
}

void NonTerminalNode::printParenthesised(CompilerState &cs) {
	type->shortPrint(cs);
	cs.os << '(';
	printAllChildren(cs);
	cs.os << ')';
}

void NonTerminalNode::printFPIF(CompilerState &cs) {
	if (children.size() > 1) {
		printParenthesised(cs);
	} else {
		printAllChildren(cs);
	}
}
