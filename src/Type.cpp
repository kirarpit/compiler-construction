#include<Logger.h>
#include<Node.h>
#include<TerminalNode.h>
#include<CompilerState.h>
#include<OutputStream.h>
#include<Type.h>
#include<TypeFactory.h>
#include<ErrorStream.h>

#define XX(a, b) b,
const std::string Type::TS[] = { TYPE_LIST };
#undef XX

Type::Type(int name, int size) :
		typeName(name), size(size), typeOf(NULL) {
	Logger::logConst(__CLASS_NAME__);
}

Type::~Type() {
	Logger::logDest(__CLASS_NAME__);
}

bool Type::operator<(const Type &t) const {
	if (size < t.size)
		return true;
	else if (size > t.size)
		return false;

	if (typeName < t.typeName)
		return true;
	else if (typeName > t.typeName)
		return false;

	if (typeOf != t.typeOf) {
		if (typeOf == NULL)
			return true;
		if (t.typeOf == NULL)
			return false;

		return typeOf < t.typeOf;
	}

	return false;
}

void Type::print(CompilerState &cs) {
	recursivePrint(cs, this, false);
}

void Type::shortPrint(CompilerState &cs) {
	cs.os << " ";
	recursivePrint(cs, this, true);
	cs.os << ":";
}

void Type::recursivePrint(CompilerState &cs, Type *type, bool shortForm) {
	if (!type) {
		return;
	}

	recursivePrint(cs, type->typeOf, shortForm);
	if (type->typeName == TP_ARRAY) {
		std::ostringstream output;
		output << type->size;
		cs.os << "[" << output.str() << "]";
	} else if (type->typeName == TP_POINTER) {
		cs.os << "[]";
	} else if (type->typeName == TP_BOOL) {
		if (shortForm)
			cs.os << "B";
		else
			cs.os << "bool";

	} else if (type->typeName == TP_SIGNED) {
		if (shortForm)
			cs.os << "S";
		else
			cs.os << "signed";

	} else if (type->typeName == TP_UNSIGNED) {
		if (shortForm)
			cs.os << "U";
		else
			cs.os << "unsigned";
	}
}

Type* Type::deref(CompilerState &cs, Token tn, int tp) {
	if (typeOf == NULL) {
		cs.es.reportTypeError(cs, tn, this,
				"indirection requires pointer operand");
	}
	if (typeName != tp) {
		cs.es.reportTypeError(cs, tn, this, "type array and pointer mismatch");
	}

	return typeOf;
}

bool Type::isSigned() {
	if (typeName == TP_SIGNED && typeOf == NULL)
		return true;
	return false;
}

bool Type::isUnsigned() {
	if (typeName == TP_UNSIGNED && typeOf == NULL)
		return true;
	return false;
}

bool Type::isBool() {
	if (typeName == TP_BOOL && typeOf == NULL)
		return true;
	return false;
}

bool Type::isPointer() {
	if (typeName == TP_POINTER)
		return true;
	return false;
}

bool Type::isNumericType() {
	if (isSigned() || isBool() || isUnsigned()) {
		return true;
	}
	return false;
}

Type* Type::getOperatorType(CompilerState &cs, Token tkn, Type *t1, Type *t2) {
	Logger::log("Getting Operator Type");

	bool error = false;
	if ((tkn.type & TT_TERM_OP) || (tkn.type & TT_FACTOR_OP)) {
		if ((t1->isSigned() || t1->isUnsigned()) && t1 == t2)
			return t1;
		else if (t1->isUnsigned() && t2->isSigned())
			return t1;
		else if (t1->isSigned() && t2->isUnsigned())
			return t2;
		else {
			error = true;
		}
	} else if (tkn.type & TT_REL_OP) {
		if ((t1->isSigned() || t1->isUnsigned() || t1->isPointer())
				&& t2 == t1) {
			return cs.tf.getPrimType(TP_BOOL);
		} else {
			error = true;
		}
	} else if (tkn.type & TT_EQ_OP) {
		if (t2 == t1 || (t1->isNumericType() && t2->isNumericType())) {
			return cs.tf.getPrimType(TP_BOOL);
		} else {
			error = true;
		}
	} else if (tkn.value == "&&" || tkn.value == "||") {
		if (t1->isBool() && t2 == t1) {
			return cs.tf.getPrimType(TP_BOOL);
		} else {
			error = true;
		}
	} else if (tkn.value == "=") {
		if (t1->isNumericType() && t2->isNumericType()) {
			return t1;
		} else if (t1->isPointer() && t1 == t2) {
			return t1;
		} else {
			error = true;
		}
	} else if (tkn.value == ",") {
		return t2;
	}

	if (error) {
		cs.es.reportOpTypeError(cs, tkn, t1, t2,
				"invalid operands to binary expression ('%t1' and '%t2')");
	}

	return NULL;
}

Node* Type::constantFold(CompilerState &cs, Token tkn, Token t1, Token t2) {
	int val = -1;
	std::ostringstream output;

	int lhs = t1.getIntVal();
	int rhs = t2.getIntVal();

	if (tkn.value == "+") {
		val = lhs + rhs;
	} else if (tkn.value == "-") {
		val = lhs - rhs;
	} else if (tkn.value == "*") {
		val = lhs * rhs;
	} else if (tkn.value == "/") {
		val = lhs / rhs;
	} else if (tkn.value == "<") {
		val = (lhs < rhs) ? 1 : 0;
	} else if (tkn.value == "<=") {
		val = (lhs <= rhs) ? 1 : 0;
	} else if (tkn.value == ">") {
		val = (lhs > rhs) ? 1 : 0;
	} else if (tkn.value == ">=") {
		val = (lhs >= rhs) ? 1 : 0;
	} else if (tkn.value == "==") {
		val = (lhs == rhs) ? 1 : 0;
	} else if (tkn.value == "!=") {
		val = (lhs != rhs) ? 1 : 0;
	} else if (tkn.value == "&&") {
		val = (lhs && rhs) ? 1 : 0;
	} else if (tkn.value == "||") {
		val = (lhs || rhs) ? 1 : 0;
	} else if (tkn.value == ",") {
		val = rhs;
	} else if (tkn.value == "=") {
		cs.es.reportTypeError(cs, tkn, NULL, "expression is not assignable");
		return NULL;
	}

	output << val;
	return new TerminalNode(Token(TT_NUM, output.str()));
}
