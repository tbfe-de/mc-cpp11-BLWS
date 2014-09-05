/* Exercise: Bind/demo.cpp
 * ============================================================================
 * Boost Library Workshop -- Demo Program for 'Boost.Bind'
 * Supplied by: Technische Beratung fuer EDV, D-64380 Rossdorf, Germany
 * Author and Copyright (2012): Dipl.-Ing. Martin Weitzel (www.tbfe.de)
 * ============================================================================
 * Besides introducing std::bind and std::ref, this examples makes a comparison
 * to boost::bind and boost::ref and also show existing differences (at least
 * between boost 1.49 and GCC 4.6, where this was tried first).
 * Especially in C++11 argument default values for functions are not honored
 * though they are for functors, and while with boost::bind, as a work-around
 * such functions may be replaced by overloaded versions, this still not works
 * with C++11.
*/

// If NOT defined, compiler must not include its own versions in namespace std.
// For GCC this means -std=c++0x must NOT be present in the command line!
//
#define CPP11_bind_and_ref

// if NOT defined, one of the tests below will not compile and must be omitted
//
#define USE_OVERLOADING_INSTEAD_OF_ARG_DEFAULT_VALUE

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                             Standard Library
#include <algorithm>
#include <functional>
#include <iostream>
#include <sstream>

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                              Boost Libraries
#ifndef CPP11_bind_and_ref
#include <boost/bind.hpp>
#include <boost/ref.hpp>
#endif

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                             Helper Functions
#ifndef USE_OVERLOADING_INSTEAD_OF_ARG_DEFAULT_VALUE
void printFunction(std::ostream& os, const int val, const char sep = ' ') {
	os << val << sep;
}
#else
// Overloading used as work-around for default arguments here:
void printFunction(std::ostream& os, const int val, const char sep) {
	os << val << sep;
}
#ifndef CPP11_bind_and_ref
void printFunction(std::ostream& os, const int val) {
	printFunction(os, val, ' ');
}
#endif
#endif

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                              Helper Functors
struct PrintFunctor {
	typedef void result_type;
	// (Default argument for functors work as expected.)
	void operator()(std::ostream& os, const int val, const char sep = ' ') {
		os << val << sep;
	}
};

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                               Helper Classes
class PrinterClass {
	std::ostream& os;
public:
	PrinterClass(std::ostream& os_)
		: os(os_)
	{}
#ifdef USE_OVERLOADING_INSTEAD_OF_ARG_DEFAULT_VALUE
	void print(const int val, const char sep = ' ') const {
		os << val << sep;
	}
#else
	void print(const int val, const char sep = ' ') const {
		os << val << sep;
	}
	void print(const int val) const {
		print(val, ' ');
	}
#endif
};

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                              Data to Process
const int data[] = { 3, 7, 21, 147, 3187 };
const int* const data_end = data + (sizeof data / sizeof data[0]);

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                          Expectation Checker
#include "Util/CK/CK.h"

int main() {

#ifndef CPP11_bind_and_ref
	using boost::bind;
	using boost::ref;
#else
	using std::bind;
	using std::ref;
	using std::placeholders::_1;
#endif

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#ifndef CPP11_bind_and_ref
#ifdef USE_OVERLOADING_INSTEAD_OF_ARG_DEFAULT_VALUE
{
CK_section("Print function with bind (1 arg) ........................."	)
	std::ostringstream output;
	std::for_each(
		data, data_end,
		std::bind(printFunction, ref(output), _1)
	);
CK_compare(output.str()	,	"3 7 21 147 3187 "			)	
}
#endif
#endif
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
{
CK_section("Print function with bind (2 args) ........................"	)
	std::ostringstream output;
	std::for_each(
		data, data_end,
		bind(printFunction, ref(output), _1, ';')
	);
CK_compare(output.str()	,	"3;7;21;147;3187;"			)	
}
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
{
CK_section("Print functor with bind .................................."	)
	std::ostringstream output;
	std::for_each(
		data, data_end,
		bind(PrintFunctor(), ref(output), _1)
	);
CK_compare(output.str()	,	"3 7 21 147 3187 "			)	
}
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
{
CK_section("Print functor with bind (alternative) ...................."	)
	std::ostringstream output;
	std::for_each(
		data, data_end,
		bind(PrintFunctor(), ref(output), _1, ';')
	);
CK_compare(output.str()	,	"3;7;21;147;3187;"			)	
}
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
{
#ifndef CPP11_bind_and_ref
#ifdef USE_OVERLOADING_INSTEAD_OF_ARG_DEFAULT_VALUE
CK_section("Printer class with member 'print' function (1 arg) ......."	)
	std::ostringstream output;
	std::for_each(
		data, data_end,
		bind(&PrinterClass::print, PrinterClass(output),  _1)
	);
CK_compare(output.str()	,	"3 7 21 147 3187 "			)
#endif
#endif
}
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
{
CK_section("Printer class with member 'print' function (2 args) ......"	)
	std::ostringstream output;
	std::for_each(
		data, data_end,
		bind(&PrinterClass::print, PrinterClass(output),  _1, ';')
	);
CK_compare(output.str()	,	"3;7;21;147;3187;"			)
}
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
}
