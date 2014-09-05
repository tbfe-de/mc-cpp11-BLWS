#include "Util/CK/CK.h"

#include <boost/variant.hpp>

#include <iostream>
	using std::cout;
	using std::endl;

#include <string>
	using std::string;

class A {
public:
	A(int) {}
};

class B {
public:
	B(int = 0) {}
};


class C {
public:
	C(int, char) {}
};



int main() {
		boost::variant<B, A, C> x;
		
CK_section(	"Explicit Construction of A ..........."		)
		boost::variant<A, B, C> a(A(2));
CK_compare(	a.type().name()			, typeid(A).name()	)
		boost::variant<A, B, C> b(B(2));

CK_section(	"Explicit Construction of B ..........."		)
CK_compare(	b.type().name()			, typeid(B).name()	)

CK_section(	"Explicit Construction of C ..........."		)
		boost::variant<A, B, C> c(C(2, 'z'));
CK_compare(	c.type().name()			, typeid(C).name()	)

}
