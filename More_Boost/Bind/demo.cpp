/* Exercise: Bind/demo.cpp
 * ============================================================================
 * Boost Library Workshop -- Demo Program for 'Boost.Bind'
 * Supplied by: Technische Beratung fuer EDV, D-64380 Rossdorf, Germany
 * Author and Copyright (2011): Dipl.-Ing. Martin Weitzel (www.tbfe.de)
 * ============================================================================
*/
#define	X_SOLVED    1							  /*?#*/

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                             Standard Library
#include <algorithm>
#include <functional>
#include <iostream>
#include <sstream>

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                              Boost Libraries
#include <boost/bind.hpp>
#include <boost/ref.hpp>

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                             Helper Functions
void printFunction(std::ostream& os, const int val) {
	os << val << ' ';
}

void printFunction2(std::ostream& os, const int val, char sep) {
	os << val << sep;
}

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                              Helper Functors
struct PrintFunctor {
	typedef void result_type;
	void operator()(std::ostream& os, const int val, char sep = ' ') {
		os << val << sep;
	}
};

class PrinterClass {
	std::ostream& os;
	const char sep;
public:
	PrinterClass(std::ostream& os_, const char sep_ = ' ')
		: os(os_), sep(sep_)
	{}
	void print(const int val) const {
		os << val << sep;
	}
};

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                              Data to Process
const int data[] = { 3, 7, 21, 147, 3187 };
const int* const data_end = data + (sizeof data / sizeof data[0]);

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                          Expectation Checker
#include "Util/CK/CK.h"

int main() {

	// With C++ 11 functions are moved to std::
	// using std::bind;
	// using std::ref;

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
{
CK_section("Print function (1st version - std::bind1st) .............."	)
	std::ostringstream output;
	std::for_each(
		data, data_end,
		std::bind1st(ptr_fun(printFunction), output)
	);
CK_compare(output.str()	,	"3 7 21 147 3187 "			)	
}
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
{
CK_section("Print function (1st version - bind) ......................"	)
	std::ostringstream output;
	std::for_each(
		data, data_end,
		boost::bind(printFunction, ref(output), _1)
	);
CK_compare(output.str()	,	"3 7 21 147 3187 "			)	
}
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
{
CK_section("Print function (2nd version - bind) ......................"	)
	std::ostringstream output;
	std::for_each(
		data, data_end,
		boost::bind(printFunction2, ref(output), _1, ';')
	);
CK_compare(output.str()	,	"3;7;21;147;3187;"			)	
}
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
{
CK_section("Print functor (bind) ....................................."	)
	std::ostringstream output;
	std::for_each(
		data, data_end,
		boost::bind(PrintFunctor(), ref(output), _1)
	);
CK_compare(output.str()	,	"3 7 21 147 3187 "			)	
}
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
{
CK_section("Printer class with member function (std::bind1st) ........"	)
	std::ostringstream output;
	PrinterClass dp(output, ';');
	std::for_each(
		data, data_end,
		std::bind1st(std::mem_fun_ref(&PrinterClass::print), dp)
	);
CK_compare(output.str()	,	"3;7;21;147;3187;"			)	
}
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
{
CK_section("Printer class with member function (bind) ................"	)
	std::ostringstream output;
	PrinterClass dp(output, ';');
	std::for_each(
		data, data_end,
		boost::bind(&PrinterClass::print, dp,  _1)
	);
CK_compare(output.str()	,	"3;7;21;147;3187;"			)	
}
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
{
CK_section("Printer class with member function via c'tor (bind) ......"	)
	std::ostringstream output;
	std::for_each(
		data, data_end,
		boost::bind(&PrinterClass::print, PrinterClass(output),  _1)
	);
CK_compare(output.str()	,	"3 7 21 147 3187 "			)
}
}
