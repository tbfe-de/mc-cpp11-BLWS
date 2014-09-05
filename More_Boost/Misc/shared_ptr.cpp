#include <iostream>
using std::cout;
using std::endl;

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

class Res {
public:
	Res() {
		cout << "Resource " << this << " erzeugt (Default)" << endl;
	}
	Res(const Res& rhs) {
		cout << "Resource " << this << " erzeugt "
		        " als Kopie von " << &rhs << endl;
	}
	Res& operator=(const Res& rhs) {
		cout << "Resource " << this << " zugewiesen"
 			" von " << &rhs << endl;
		return *this;
	}
	~Res() {
		cout << "Resource " << this << " freigegeben" << endl;
	}
};

void g() {
	//throw "error";
}

shared_ptr<Res> foo() {
	shared_ptr<Res> p(new Res());
	shared_ptr<Res> p2;
	cout << "p = " << p.get() << endl;
	cout << "p2 = " << p2.get() << endl;
	p2 = p;
	cout << "p = " << p.get() << endl;
	cout << "p2 = " << p2.get() << endl;
	Res s;
	g();
	return p2;
}

int main() {
	shared_ptr<Res> r;
	try {
		r = foo();
		cout << "nach Aufruf von foo" << endl;
	}
	catch (const char *) {
		cout << "caught exception" << endl;
	}
	cout << "nach try-catch" << endl;
}



