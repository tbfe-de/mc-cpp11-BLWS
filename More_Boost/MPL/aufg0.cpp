#if 0

template<bool v> 
struct bool_ {
	static const bool value= v;
};

#else

#include <boost/mpl/bool.hpp>
using boost::mpl::bool_;

#endif

// -------------------------------------- Count number of bits set to 1
//

// runtime version
//
int count_bits(unsigned long v) {
	return (v == 0)
		? 0
		: count_bits(v >> 1) + (v & 1);
}

// compiletime version
//
// ... to-do ....

// ---------------------------------- Find highest bit that is set to 1
//

// runtime version
//
int high_bit(unsigned long v) {
	return (v == 0)
		? -1
		: high_bit(v >> 1) + 1;
}

// compiletime version
//
// ... to-do ....

// -------------------------------- Find out if value is a power of two
//

// runtime version
//
bool is_pwrof2(unsigned long v) {
	if (v == 0) return false;
	if (v == 1) return true;
	const bool tmp1 = (v & 1);
	const bool tmp2 = is_pwrof2(v >> 1);
	const bool tmp3 = tmp1 && tmp2;
	return tmp3;
}

// compiletime version
//
template<unsigned long V>
struct is_pwrof2_tmpl {
	typedef bool_<!(V & 1) && is_pwrof2_tmpl<V >> 1>::value> type;
	static const bool value= type::value; 
};

template<>
struct is_pwrof2_tmpl<0> {
	typedef bool_<false> type;
	static const bool value= type::value; 
};

template<>
struct is_pwrof2_tmpl<1> {
	typedef bool_<true> type;
	static const bool value= type::value; 
};

// -------------------------------- Find out if value is a power of two
//

// runtime version (helper)
//
unsigned int mid_range(unsigned int low, unsigned int high) {
	return low + (high - low) / 2;
}

// runtime version (helper)
//
unsigned int find_sqrt(unsigned int low_estimate, unsigned int n, unsigned int high_estimate) {
	const int mid= mid_range(low_estimate, high_estimate);
	return mid == low_estimate
		? mid
		: mid*mid <= n
		? find_sqrt(mid, n, high_estimate)
		: find_sqrt(low_estimate, n, mid);
}
	
// runtime version
//
unsigned int square_root(unsigned int n) {
	return find_sqrt(0, n, n/2);
}

// ---------------------------------------------------------- TEST CODE

#include "Util/CK/CK.h"

int main() {

CK_section(	"Power of two (runtime) ........"			)
CK_compare(	is_pwrof2(0)			, false			)
CK_compare(	is_pwrof2(1)			, true			)
CK_compare(	is_pwrof2(2)			, true			)
CK_compare(	is_pwrof2(3)			, false			)
CK_compare(	is_pwrof2(4)			, true			)
CK_compare(	is_pwrof2(5)			, false			)
CK_compare(	is_pwrof2(3)			, false			)

CK_section(	"Power of two (compile time) ..."			)
CK_compare(	is_pwrof2_tmpl<1>::type::value	, true			)
CK_compare(	is_pwrof2_tmpl<2>::type::value	, true			)
CK_compare(	is_pwrof2_tmpl<3>::type::value	, false			)
CK_compare(	is_pwrof2_tmpl<4>::type::value	, true			)
CK_compare(	is_pwrof2_tmpl<5>::type::value	, false			)
CK_compare(	is_pwrof2_tmpl<6>::type::value	, false			)
CK_compare(	is_pwrof2_tmpl<7>::type::value	, false			)
CK_compare(	is_pwrof2_tmpl<8>::type::value	, true			)
CK_compare(	is_pwrof2_tmpl<9>::type::value	, false			)

}
