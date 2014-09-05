/*
 ==============================================================================
 Demonstrate new C++-11 "Curly Brace" Initializer for Standard-Container
 ==============================================================================
*/
//#define CPP11_ListInitializer
//#define CPP11_ListInitializer_in_ctor
//#define CPP11_ListInitializer_with_assign

// ----------------------------------------------------------------------------
//                                                    From Standard C++ Library
#include <algorithm>
#include <deque>
#include <iostream>
#include <list>
#include <numeric>
#include <vector>
using namespace std;

// ----------------------------------------------------------------------------
//                                                          From Boost-Platform
#include <boost/array.hpp>

template<class Container>
double process_stl_sequential_container() {

#ifndef CPP11_ListInitializer
	Container data;
	data.push_back(1.2);
	data.push_back(3.4);
	data.push_back(5.6);
#elif defined(CPP11_ListInitializer_with_assign)
	Container data = { 1.2, 3.4, 5.6 };
#elif defined(CPP11_ListInitializer_in_ctor)
	Container data({ 1.2, 3.4, 5.6 });
#else
	Container data{ 1.2, 3.4, 5.6 };
#endif
	return accumulate(
		data.begin(),	// Start-Iterator
		data.end(),	// End-Iterator
		0.0		// Akkumulator-Anfangswert
	);
}

double process_boost_array_wrapper() {

#ifndef CPP11_ListInitializer
	boost::array<double, 3> data = {{
		1.2, 3.4, 5.6
	}};
#else
	// Note: as of boost 1.49 other forms of new C++11
	// initializer are not (yet?) supported.
	// (Attempting an explanation: C++11 syntax would
	// be possible but result in less performance as
	// initialization takes place in a loop at runtime
	// not at compile time - which would be the case
	// with "old" syntax, at least when the array has
	// "static" or "const static" storage qualifiers.)
	// Shown below is the "relaxed" old syntax which
	// is accepted by g++, though a warning is emitted
	// for -Wall.
	//
	boost::array<double, 3> data = {
		1.2, 3.4, 5.6
	};
#endif
	return accumulate(
		data.begin(),	// Start-Iterator
		data.end(),	// End-Iterator
		0.0		// Akkumulator-Anfangswert
	);
}
#include "Util/CK/CK.h"

int main() {

CK_section(	"std::vector<double> ......."				)
CK_compare(	process_stl_sequential_container< vector<double> >()
						, (1.2 + 3.4 + 5.6)	)

CK_section(	"std::list<double> ........."				)
CK_compare(	process_stl_sequential_container< list<double> >()
						, (1.2 + 3.4 + 5.6)	)

CK_section(	"std::deque<double> ........"				)
CK_compare(	process_stl_sequential_container< deque<double> >()
						, (1.2 + 3.4 + 5.6)	)

CK_section(	"boost::array<double> ......"				)
CK_compare(	process_boost_array_wrapper()	, (1.2 + 3.4 + 5.6)	)

}
