#include <iostream>
using std::cout;
using std::endl;

#include <memory>
using std::auto_ptr;

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

auto_ptr<Res> foo() {
	auto_ptr<Res> p(new Res());
	auto_ptr<Res> p2(new Res());
	cout << "p = " << p.get() << endl;
	cout << "p2 = " << p2.get() << endl;
	p2 = p;
	cout << "p = " << p.get() << endl;
	cout << "p2 = " << p2.get() << endl;
	Res s;
	g();
	return p;
}

int main() {
	try {
		auto_ptr<Res> r;
		foo();
	}
	catch (const char *) {
		cout << "caught exception" << endl;
	}
}



