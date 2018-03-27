#include<TypeInfo.h>
#include<Logger.h>
#include<Node.h>
#include<TerminalNode.h>
#include<CompilerState.h>
#include<OutputStream.h>

TypeInfo::TypeInfo(int name, int size) :
		type(name), size(size), typeOf(NULL) {
	Logger::log("TypeInfo Constructor Called");
}

TypeInfo::~TypeInfo() {
	Logger::log("TypeInfo Destructor Called");
	if (typeOf)
		delete typeOf;
}

#define XX(a, b) b,
const std::string TypeInfo::Type[] = { TYPE_LIST };
#undef XX

void TypeInfo::print(CompilerState &cs) {
	recursivePrint(cs, this, false);
}

void TypeInfo::shortPrint(CompilerState &cs) {
	cs.os << " ";
	recursivePrint(cs, this, true);
	cs.os << ":";
}

void TypeInfo::recursivePrint(CompilerState &cs, TypeInfo *type,
		bool shortForm) {
	if (!type) {
		return;
	}

	recursivePrint(cs, type->typeOf, shortForm);
	if (type->type == TP_ARRAY) {
		std::ostringstream output;
		output << type->size;
		cs.os << "[" << output.str() << "]";
	} else if (type->type == TP_POINTER) {
		cs.os << "[]";
	} else if (type->type == TP_BOOL) {
		if (shortForm)
			cs.os << "B";
		else
			cs.os << "bool";

	} else if (type->type == TP_SIGNED) {
		if (shortForm)
			cs.os << "S";
		else
			cs.os << "signed";
	} else if (type->type == TP_UNSIGNED) {
		if (shortForm)
			cs.os << "U";
		else
			cs.os << "unsigned";
	}
}

TypeInfo* TypeInfo::addr() {
	TypeInfo *t = new TypeInfo(TP_POINTER, 0);
	t->typeOf = this;
	return t;
}

TypeInfo* TypeInfo::deref(int tp) {
	Logger::log("TypeInfo deref");

	if (typeOf == NULL) {
		//error
		exit(1);
	}
	if (type != tp) {
		//error
		exit(1);
	}
	return typeOf;
}

bool TypeInfo::isSigned() {
	if (type == TP_SIGNED && typeOf == NULL)
		return true;
	return false;
}

bool TypeInfo::isUnsigned() {
	if (type == TP_UNSIGNED && typeOf == NULL)
		return true;
	return false;
}

bool TypeInfo::isBool() {
	if (type == TP_BOOL && typeOf == NULL)
		return true;
	return false;
}

bool TypeInfo::isPointer() {
	if (type == TP_POINTER)
		return true;
	return false;
}

bool TypeInfo::isNumericType() {
	if (isSigned() || isBool() || isUnsigned()) {
		return true;
	}
	return false;
}

bool TypeInfo::isEqual(TypeInfo *t1) {
	if (t1->type == type && t1->size == size) {
		if (typeOf == NULL && t1->typeOf == NULL)
			return true;
		if (typeOf == NULL || t1->typeOf == NULL)
			return false;

		return typeOf->isEqual(t1->typeOf);
	} else {
		return false;
	}
}

TypeInfo* TypeInfo::getOperandType(Token tkn, TypeInfo *t1, TypeInfo *t2) {
	if ((tkn.type & TT_TERM_OP) || (tkn.type & TT_FACTOR_OP)) {
		if (t1->isSigned() && t2->isSigned())
			return t1;
		else if (t1->isUnsigned() && t2->isSigned())
			return t1;
		else if (t1->isUnsigned() && t2->isUnsigned())
			return t1;
		else if (t1->isSigned() && t2->isUnsigned())
			return t2;
		else {
			//error
			exit(1);
		}
	} else if (tkn.type & TT_REL_OP) {
		if ((t1->isSigned() || t1->isUnsigned() || t1->isPointer())
				&& t2->isEqual(t1)) {
			return new TypeInfo(TP_BOOL, 0);
		} else {
			//error
			exit(1);
		}
	} else if (tkn.type & TT_EQ_OP) {
		if (t2->isEqual(t1) || (t1->isNumericType() && t2->isNumericType())) {
			return new TypeInfo(TP_BOOL, 0);
		} else {
			//error
			exit(1);
		}
	} else if (tkn.value == "&&" || tkn.value == "||") {
		if (t1->isBool() && t2->isEqual(t1)) {
			return new TypeInfo(TP_BOOL, 0);
		} else {
			//error
			exit(1);
		}
	} else if (tkn.value == "=") {
		if (t1->isNumericType() && t2->isNumericType()) {
			return t1;
		} else if (t1->isPointer() && t1->isEqual(t2)) {
			return t1;
		} else {
			//error
			exit(1);
		}
	} else if (tkn.value == ",") {
		return t2;
	}

	return NULL;
}

Node* TypeInfo::constantFold(Token tkn, Token t1, Token t2) {
	int val = -1;
	std::ostringstream output;

	if ((t1.type & TT_NUM) && (t2.type & TT_NUM)) {

		if ((tkn.type & TT_TERM_OP) || (tkn.type & TT_FACTOR_OP)) {
			if (tkn.value == "+") {
				val = t1.getIntVal() + t2.getIntVal();
			} else if (tkn.value == "-") {
				val = t1.getIntVal() - t2.getIntVal();
			} else if (tkn.value == "*") {
				val = t1.getIntVal() * t2.getIntVal();
			} else if (tkn.value == "/") {
				val = t1.getIntVal() / t2.getIntVal();
			}
		} else if (tkn.type & TT_REL_OP) {
			if (tkn.value == "<") {
				val = (t1.getIntVal() < t2.getIntVal()) ? 1 : 0;
			} else if (tkn.value == "<=") {
				val = (t1.getIntVal() <= t2.getIntVal()) ? 1 : 0;
			} else if (tkn.value == ">") {
				val = (t1.getIntVal() > t2.getIntVal()) ? 1 : 0;
			} else if (tkn.value == ">=") {
				val = (t1.getIntVal() >= t2.getIntVal()) ? 1 : 0;
			}
		} else if (tkn.type & TT_EQ_OP) {
			if (tkn.value == "==") {
				val = (t1.getIntVal() == t2.getIntVal()) ? 1 : 0;
			} else if (tkn.value == "!=") {
				val = (t1.getIntVal() != t2.getIntVal()) ? 1 : 0;
			}
		} else if (tkn.value == "&&" || tkn.value == "||") {
			if (tkn.value == "&&") {
				val = (t1.getIntVal() && t2.getIntVal()) ? 1 : 0;
			} else if (tkn.value == "||") {
				val = (t1.getIntVal() || t2.getIntVal()) ? 1 : 0;
			}
		} else if (tkn.value == "=") {
			//error
			exit(1);
		} else if (tkn.value == ",") {
			val = t1.getIntVal(), t2.getIntVal();
		}
	} else {
		//error
		exit(1);
	}

	output << val;
	return new TerminalNode(Token(TT_NUM, output.str()));
}
