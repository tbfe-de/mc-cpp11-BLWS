#include <iostream>
using std::cout;
using std::endl;

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
	throw "error";
}

void foo() {
	Res *p = new Res();
	Res s;
	g();
	delete p;
}

int main() {
	try {
		foo();
	}
	catch (const char *) {
		cout << "caught exception" << endl;
	}
}



