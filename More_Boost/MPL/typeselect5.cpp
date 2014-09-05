#include <iostream>

enum day { MON, TUE, WED, THU, FRI, SAT, SUN };

struct workday {
	static void doIt() {
		std::cout << "working nine to five" << std::endl;
	}
};

struct weekend {
	static void doIt() {
		std::cout << "stay at home" << std::endl;
	}
};

#define T WED

#include <boost/mpl/if.hpp>
	using boost::mpl::bool_;
	using boost::mpl::if_;

int main() {
	typedef bool_<T != SAT && T != SUN> isWorkday;
	if_< isWorkday,
		workday,
		weekend
	>::type::doIt();
}
