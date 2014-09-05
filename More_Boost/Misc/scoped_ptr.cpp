#include <iostream>
using std::cout;
using std::endl;

#include <boost/scoped_ptr.hpp>
using boost::scoped_ptr;

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

void foo() {
	scoped_ptr<Res> p(new Res());
	scoped_ptr<Res> p2;
	cout << "p = " << p.get() << endl;
	cout << "p2 = " << p2.get() << endl;
	swap(p2, p);
	cout << "p = " << p.get() << endl;
	cout << "p2 = " << p2.get() << endl;
	Res s;
	g();
}

int main() {
	try {
		foo();
	}
	catch (const char *) {
		cout << "caught exception" << endl;
	}
}



