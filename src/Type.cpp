#include<Logger.h>
#include<Node.h>
#include<TerminalNode.h>
#include<CompilerState.h>
#include<OutputStream.h>
#include <Type.h>

Type::Type(int name, int size) :
		type(name), size(size), typeOf(NULL) {
	Logger::log("TypeInfo Constructor Called");
}

Type::~Type() {
	Logger::log("TypeInfo Destructor Called");
	if (typeOf)
		delete typeOf;
}

#define XX(a, b) b,
const std::string Type::TS[] = { TYPE_LIST };
#undef XX

void Type::print(CompilerState &cs) {
	recursivePrint(cs, this, false);
}

void Type::shortPrint(CompilerState &cs) {
	cs.os << " ";
	recursivePrint(cs, this, true);
	cs.os << ":";
}

void Type::recursivePrint(CompilerState &cs, Type *type,
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

Type* Type::addr() {
	Type *t = new Type(TP_POINTER, 0);
	t->typeOf = this;
	return Type::deepCopy(t);
}

Type* Type::deref(int tp) {
	Logger::log("TypeInfo deref");

	if (typeOf == NULL) {
		//error
		exit(1);
	}
	if (type != tp) {
		//error
		exit(1);
	}
	return Type::deepCopy(typeOf);
}

bool Type::isSigned() {
	if (type == TP_SIGNED && typeOf == NULL)
		return true;
	return false;
}

bool Type::isUnsigned() {
	if (type == TP_UNSIGNED && typeOf == NULL)
		return true;
	return false;
}

bool Type::isBool() {
	if (type == TP_BOOL && typeOf == NULL)
		return true;
	return false;
}

bool Type::isPointer() {
	if (type == TP_POINTER)
		return true;
	return false;
}

bool Type::isNumericType() {
	if (isSigned() || isBool() || isUnsigned()) {
		return true;
	}
	return false;
}

bool Type::isEqual(Type *t1) {
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

Type* Type::getOperandType(Token tkn, Type *t1, Type *t2) {
	if ((tkn.type & TT_TERM_OP) || (tkn.type & TT_FACTOR_OP)) {
		if (t1->isSigned() && t2->isSigned())
			return new Type(TP_SIGNED, 0);
		else if (t1->isUnsigned() && t2->isSigned())
			return new Type(TP_UNSIGNED, 0);
		else if (t1->isUnsigned() && t2->isUnsigned())
			return new Type(TP_UNSIGNED, 0);
		else if (t1->isSigned() && t2->isUnsigned())
			return new Type(TP_UNSIGNED, 0);
		else {
			//error
			exit(1);
		}
	} else if (tkn.type & TT_REL_OP) {
		if ((t1->isSigned() || t1->isUnsigned() || t1->isPointer())
				&& t2->isEqual(t1)) {
			return new Type(TP_BOOL, 0);
		} else {
			//error
			exit(1);
		}
	} else if (tkn.type & TT_EQ_OP) {
		if (t2->isEqual(t1) || (t1->isNumericType() && t2->isNumericType())) {
			return new Type(TP_BOOL, 0);
		} else {
			//error
			exit(1);
		}
	} else if (tkn.value == "&&" || tkn.value == "||") {
		if (t1->isBool() && t2->isEqual(t1)) {
			return new Type(TP_BOOL, 0);
		} else {
			//error
			exit(1);
		}
	} else if (tkn.value == "=") {
		if (t1->isNumericType() && t2->isNumericType()) {
			return Type::deepCopy(t1);
		} else if (t1->isPointer() && t1->isEqual(t2)) {
			return Type::deepCopy(t1);
		} else {
			//error
			exit(1);
		}
	} else if (tkn.value == ",") {
		return Type::deepCopy(t2);
	}

	return NULL;
}

Node* Type::constantFold(Token tkn, Token t1, Token t2) {
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

Type* Type::deepCopy(Type *type) {
	if (!type)
		return NULL;

	Type *newType = deepCopy(type->typeOf);
	Type *temp = new Type(type->type, type->size);
	temp->typeOf = newType;
	return temp;
}
