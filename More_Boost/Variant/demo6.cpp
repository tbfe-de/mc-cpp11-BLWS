#include <boost/variant.hpp>
#include <boost/call_traits.hpp>

#include <iostream>
using std::cout;
using std::endl;
using std::ostream;

#include <string>
using std::string;

typedef boost::variant<int, double, string> my_variant_type;

template<class T>
struct caller {
	typedef typename boost::call_traits<T>::param_type param_type;
	static void print(ostream& os, param_type e) {
		cout << e << endl;
	}
};

struct print_visitor : boost::static_visitor<> {
	// general case
	template<class T>
	void operator()(const T& e) const {
		caller<T>::print(cout, e);
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

	print_visitor pv;
	boost::apply_visitor(pv, x);
	boost::apply_visitor(pv, y);
	boost::apply_visitor(pv, z);

}
