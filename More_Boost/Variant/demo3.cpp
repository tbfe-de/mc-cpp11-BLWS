#include <boost/variant.hpp>

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

typedef boost::variant<string, int, double> my_variant_type;

struct print_visitor : boost::static_visitor<> {
	void operator()(int e) {
		cout << e << endl;
	}
	void operator()(double e) {
		cout << e << endl;
	}
	void operator()(const string& e) {
		cout << '"' << e << '"' << endl;
	}
};


int main() {
	my_variant_type x, y, z;
	x = 33;
	y = 1.234;
	z = "hello";

	print_visitor pv;
	boost::apply_visitor(pv, x);
	boost::apply_visitor(pv, y);
  	boost::apply_visitor(pv, z);

}
