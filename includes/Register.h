#ifndef SRC_REGISTER_H_
#define SRC_REGISTER_H_

class Register {
public:
	Register(int name) :
			name(name) {
	}
	virtual ~Register() {
	}

	int name;
};

#endif /* SRC_REGISTER_H_ */
