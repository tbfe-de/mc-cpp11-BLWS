#include <iostream>
using std::cout;
using std::endl;

#include <memory>
using std::unique_ptr;

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

unique_ptr<Res> foo() {
	unique_ptr<Res> p(new Res());
	unique_ptr<Res> p2;
	cout << "p = " << p.get() << endl;
	cout << "p2 = " << p2.get() << endl;
	swap(p2, p);
	cout << "p = " << p.get() << endl;
	cout << "p2 = " << p2.get() << endl;
	Res s;
	g();
	return p2;
}

int main() {
	try {
		unique_ptr<Res> r;
		r = foo();
	}
	catch (const char *) {
		cout << "caught exception" << endl;
	}
}



