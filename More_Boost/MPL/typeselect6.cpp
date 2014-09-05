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
	using namespace boost::mpl;

#define V 5
int main() {
#if V == 1
	typedef bool_<T != SAT && T != SUN> isWorkday;
	typedef if_<isWorkday, workday, weekend>::type kindOfDay;
	kindOfDay::doIt();
#endif
#if V == 2
	typedef bool_<T != SAT && T != SUN> isWorkday;
	typedef if_<isWorkday, workday, weekend> kindOfDay;
	kindOfDay::type::doIt();
#endif
#if V == 3
	typedef bool_<T != SAT && T != SUN>::type isWorkday;
	typedef if_<isWorkday, workday, weekend> kindOfDay;
	kindOfDay::type::doIt();
#endif
#if V == 4
	typedef bool_<T != SAT && T != SUN>::type isWorkday;
	struct kindOfDay {
		typedef if_<isWorkday, workday, weekend>::type type;
	};
	kindOfDay::type::doIt();
#endif
#if V == 5
	typedef bool_<T != SAT && T != SUN>::type isWorkday;
	struct kindOfDay : if_<isWorkday, workday, weekend> {};
	kindOfDay::type::doIt();
#endif
}
