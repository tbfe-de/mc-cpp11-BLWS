#include "Util/CK/CK.h"

#include <iostream>
#include <boost/ref.hpp>

class MyClass {
	int value;
public:
	MyClass(const int value_) : value(value_) {}
	int getValue() const { return value; }
	void squareYourSelf() {
		value *= value;
	}
};

static void squareCaller(MyClass &instance) {
	instance.squareYourSelf();
}

template<class T, class T2>
void runner(T arg, int count, T2 operation) {
	for (int i = 0; i < count; ++i)
		operation(arg);
}

int main() {
		MyClass x(2);
CK_section(	"MyClass per value ..................."			)
		runner(x, 3, &squareCaller);
CK_compare(	x.getValue(),			2			)

CK_section(	"MyClass reference wrapped ..........."			)
		runner(boost::ref(x), 3, squareCaller);
CK_compare(	x.getValue(),			256			)
		MyClass y(2);
		runner(boost::ref(y), 4, squareCaller);
CK_compare(	y.getValue(),			65536    		)
		MyClass z(3);
		runner(boost::ref(z), 4, squareCaller);
CK_compare(	z.getValue(),			43046721		)
}
