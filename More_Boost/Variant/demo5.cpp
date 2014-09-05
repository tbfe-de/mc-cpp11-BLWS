#include <boost/variant.hpp>

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

typedef boost::variant<string, int, double> my_variant_type;

template<class T>
struct CoutPrinter {
};

struct print_visitor : boost::static_visitor<> {
	// general case
	template<class T>
	void operator()(T e) const {
		cout << e << endl;
	}
#if 0
	// special case
	void operator()(const string& e) const {
		cout << '"' << e << '"' << endl;
	}
#endif
};


int main() {
	my_variant_type x, y, z;
	x = 33;
	y = 1.234;
	z = "hello";

	boost::apply_visitor(print_visitor(), x);
	boost::apply_visitor(print_visitor(), y);
	boost::apply_visitor(print_visitor(), z);

}
