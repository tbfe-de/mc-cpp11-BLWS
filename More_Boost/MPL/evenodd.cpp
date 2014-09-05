#include <boost/mpl/if.hpp>

#include <iostream>

struct even {
	static void doIt() {
		std::cout << "even" << std::endl;
	}
};

struct odd {
	static void doIt() {
		std::cout << "odd" << std::endl;
	}
};

template<int N>
struct even_odd {
	typedef typename boost::mpl::if_<
		boost::mpl::bool_<N % 2 == 0>,
		even,
		odd
	>::type type;
};

int main() {
	even_odd<123456>::type::doIt();
}
