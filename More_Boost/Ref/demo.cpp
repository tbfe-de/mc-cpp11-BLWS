#include "Util/CK/CK.h"

#include <iostream>
#include <boost/ref.hpp>
#include <boost/bind.hpp>

class MyClass {
	int value;
public:
	MyClass(int value_) : value(value_) {}
	int getValue() const { return value; }
	void doSomething() { value *= value; }
	static void doItAnotherWay(MyClass &instance) {
		instance.value *= instance.value;
	}
};

class OtherClass {
	int& value;
public:
	OtherClass(int& value_) : value(value_) {}
	void doSomething() const { value *= value; }
	static void doItAnotherWay(const OtherClass &instance) {
		instance.value *= instance.value;
	}
};


template<class T>
void runner(T arg, int max) {
	typedef typename boost::unwrap_reference<T>::type WrappedClass;
	for (int i = 0; i < max; ++i)
		static_cast<WrappedClass&>(arg).doSomething();
		//WrappedClass::doItAnotherWay(arg);
}

class MyFunctor {
	int value;
public:
	MyFunctor(int value_) : value(value_) {}
	int getValue() const { return value; }
	void operator()() { value *= value; }
};

template<class T>
void runner2(T arg, int max) {
	for (int i = 0; i < max; ++i)
		arg();
}

int main() {
		MyClass my(2);
CK_section(	"MyClass per value ..................."			)
		runner(my, 3);
CK_compare(	my.getValue(),			2			)
CK_section(	"MyClass reference wrapped ..........."			)
		runner(boost::ref(my), 3);
CK_compare(	my.getValue(),			256			)
		int xvalue = 2;
		OtherClass other(xvalue);
CK_section(	"OtherClass per value ................"			)
		runner(other, 3);
CK_compare(	xvalue,				256			)
		xvalue = 2; // reset content !!
CK_section(	"OtherClass const reference wrapped .."			)
		runner(boost::ref(other), 3);
CK_compare(	xvalue,				256			)
		xvalue = 2; // reset content !!
		runner(boost::cref(other), 3);
CK_compare(	xvalue,				256			)
		MyFunctor f(2);
		runner2(f, 3);
CK_compare(	f.getValue(),			2			)
		runner2(boost::bind<void>(boost::ref(f)), 3);
CK_compare(	f.getValue(),			256			)
}
