#include <iostream>
	using std::cout;
	using std::endl;
	using std::ostream;
#include <boost/bind.hpp>
#include <boost/signals.hpp>
#include <boost/ref.hpp>

void sayHello() {
	cout << "Hello, World!" << endl;
};

void sayHello_function(ostream &os) {
	os << "Hello, World! (function)" << endl;
};

class SayHello_functor {
	ostream& os;
public:
	SayHello_functor(ostream& os_) : os(os_) {}
	void operator()() const { 
		os << "Hello, World! (functor)" << endl;
	} 
};

// Signal with no arguments and a void return value
boost::signal<void ()> sig0;
boost::signal<void (ostream&)> sig1;
boost::signal<void ()> sig2;

int main() {
	cout << "** connect function without argument to sig0 ..." << endl;
	sig0.connect(sayHello);
	cout << "   ... and call: ";
	sig0();
	
	cout << "** connect function with argument to sig1 ..." << endl;
	sig1.connect(sayHello_function);
	cout << "   ... and call: ";
	sig1(cout);

	SayHello_functor f(std::cout);
	cout << "** connect functor with data member to sig2 ..." << endl;
	sig2.connect(f);
	cout << "   ... and call: ";
	sig2();

	cout << "** connect more to sig2 and call again:" << endl;
	sig2.connect(sayHello);
	sig2.connect(boost::bind(sayHello_function, boost::ref(cout)));
	sig2();
}
