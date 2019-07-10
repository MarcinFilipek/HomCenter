/*
 * Callback.h
 *
 *  Created on: 29 wrz 2016
 *      Author: Uzume
 */

#ifndef CALLBACK_CALLBACK_H_
#define CALLBACK_CALLBACK_H_

template<class T1 = void, class T2 = void>
class GenericCallback {
public:
	virtual ~GenericCallback() {
	}
	virtual void execute(T1 val1, T2 val2) = 0;
	virtual bool isValid() const = 0;
};

template<class T1>
class GenericCallback<T1, void> {
public:
	virtual ~GenericCallback() {
	}
	virtual void execute(T1 val1) = 0;
	virtual bool isValid() const = 0;
};

template<>
class GenericCallback<void> {
public:
	virtual ~GenericCallback() {
	}
	virtual void execute() = 0;
	virtual bool isValid() const = 0;
};

template<class dest_type, typename T1 = void, typename T2 = void>
struct Callback: public GenericCallback<T1, T2> {
public:
	Callback() :
			pobject(0), pmemfun_2(0) {
	}
	Callback(dest_type* pobject, void (dest_type::*pmemfun_2)(T1, T2)) {
		this->pobject = pobject;
		this->pmemfun_2 = pmemfun_2;
	}
	virtual void execute(T1 t1, T2 t2) {
		(pobject->*pmemfun_2)(t1, t2);
	}
	virtual bool isValid() const {
		return (pobject != 0) && (pmemfun_2 != 0);
	}
	virtual ~Callback() {
	}
private:
	dest_type* pobject;
	void (dest_type::*pmemfun_2)(T1, T2);
};

template<class dest_type, typename T1>
struct Callback<dest_type, T1, void> : public GenericCallback<T1> {
	Callback() :
			pobject(0), pmemfun_1(0) {
	}
	Callback(dest_type* pobject, void (dest_type::*pmemfun_1)(T1)) {
		this->pobject = pobject;
		this->pmemfun_1 = pmemfun_1;
	}

	virtual void execute(T1 t1) {
		(pobject->*pmemfun_1)(t1);
	}

	virtual bool isValid() const {
		return (pobject != 0) && (pmemfun_1 != 0);
	}
	virtual ~Callback() {
	}
private:
	dest_type* pobject;
	void (dest_type::*pmemfun_1)(T1);
};

template<class dest_type>
struct Callback<dest_type, void, void> : public GenericCallback<> {
	Callback() :
			pobject(0), pmemfun_0(0) {
	}
	Callback(dest_type* pobject, void (dest_type::*pmemfun_0)()) {
		this->pobject = pobject;
		this->pmemfun_0 = pmemfun_0;
	}
	virtual void execute() {
		(pobject->*pmemfun_0)();
	}
	virtual bool isValid() const {
		return (pobject != 0) && (pmemfun_0 != 0);
	}
private:
	dest_type* pobject;
	void (dest_type::*pmemfun_0)();

};


#endif /* CALLBACK_CALLBACK_H_ */
