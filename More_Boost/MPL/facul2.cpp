#include <boost/mpl/int.hpp>

template <int v>
struct facul {
	typedef boost::mpl::int_< v * facul<v-1>::type::value > type;
};

template<>
struct facul<1> {
	typedef boost::mpl::int_<1> type;
};

#include <iostream>
int main() {
	std::cout << facul<6>::type::value << std::endl;
}
