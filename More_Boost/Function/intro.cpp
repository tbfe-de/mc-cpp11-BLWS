#include <boost/function.hpp>

class one_arg_function {
	const boost::function<int (int, int)> two_arg_function;
	const int fixed_arg2;
public:
	one_arg_function(boost::function<int (int, int)> taf, int fa2)
		: two_arg_function(taf)
		, fixed_arg2(fa2)
	{}
	int operator()(int arg1) {
		return two_arg_function(arg1, fixed_arg2);
	}
};

boost::function<int (int)>	// <---------------------- result type
	fix2nd(			// <---------------------- function name
	    boost::function<int (int, int)> taf,  // <---- first arg
	    int fa2				  // <---- second arg
	) { // <------------------------------------------ begin body
		return one_arg_function(taf, fa2);
	}   // <------------------------------------------ end body	

int iadd(int a, int b) {
	return a + b;
}

int isub(int a, int b) {
	return a - b;
}

int imul(int a, int b) {
	return a * b;
}

int idiv(int a, int b) {
	return a / b;
}

#include "Util/CK/CK.h"

int main() {
		boost::function<int (int)> f;
CK_section("Always add seven ......................."	)
		f = fix2nd(iadd, 7);
CK_compare(	f(0)			, 7		)
CK_compare(	f(1)			, 8		)
CK_compare(	f(100)			, 107		)
CK_compare(	f(-7)			, 0		)

CK_section("Always subtract one ...................."	)
		f = fix2nd(isub, 1);
CK_compare(	f(0)			, -1		)
CK_compare(	f(1)			, 0		)
CK_compare(	f(100)			, 99		)
CK_compare(	f(-7)			, -8		)

CK_section("Always multiply with two ..............."	)
		f = fix2nd(imul, 2);
CK_compare(	f(0)			, 0		)
CK_compare(	f(1)			, 2		)
CK_compare(	f(100)			, 200		)
CK_compare(	f(-7)			, -14		)

CK_section("Always divide by three ................."	)
		f = fix2nd(idiv, 3);
CK_compare(	f(0)			, 0		)
CK_compare(	f(1)			, 0		)
CK_compare(	f(100)			, 33		)
CK_compare(	f(-7)			, -2		)

}
