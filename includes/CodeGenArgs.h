#ifndef SRC_CODEGENARGS_H_
#define SRC_CODEGENARGS_H_

enum {
	GET_VALUE, GET_ADDRESS
};

class CodeGenArgs {
public:
	CodeGenArgs();
	virtual ~CodeGenArgs();

	int develop;
};

#endif /* SRC_CODEGENARGS_H_ */
