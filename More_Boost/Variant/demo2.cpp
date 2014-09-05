#include <boost/variant.hpp>

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

typedef boost::variant<string, int, double> my_variant_type;

void print(const my_variant_type& param) {
	if (const string *p = boost::get<string>(&param)) {
		cout << '"' << *p << '"' << endl;
	}
	if (const int *p = boost::get<int>(&param)) {
		cout << *p << endl;
	}
	if (const double *p = boost::get<double>(&param)) {
		cout << *p << endl;
	}
}


int main() {
	my_variant_type x, y, z;
	x = 33;
	y = 1.234;
	z = "hello";

	print(x);
	print(y);
	print(z);

}
