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

int main() {
	boost::mpl::if_c<
		T != SAT && T != SUN,
		workday,
		weekend
	>::type::doIt();
}
