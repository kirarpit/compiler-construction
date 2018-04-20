#ifndef SRC_CODEGENARGS_H_
#define SRC_CODEGENARGS_H_

enum {
	GET_VALUE, GET_ADDRESS
};
enum {
	FALL_TRUE, FALL_FALSE, FALL_EITHER, FALL_NEITHER
};

enum {
	TrueL, FalseL
};

class CodeGenArgs {
public:
	CodeGenArgs();
	virtual ~CodeGenArgs();

	int develop;
	int fall;
	int l1;
	int l2;
};

#endif /* SRC_CODEGENARGS_H_ */
