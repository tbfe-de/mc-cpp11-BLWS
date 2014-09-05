/* Exercise: Call_traits/demo.cpp
 * ============================================================================
 * Boost Library Workshop -- Demo Program for 'Boost.Call_traits'
 * Supplied by: Technische Beratung fuer EDV, D-64380 Rossdorf, Germany
 * Author and Copyright (2011): Dipl.-Ing. Martin Weitzel (www.tbfe.de)
 * ============================================================================
*/
#define	X_SOLVED    5	/*?#*/

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                             Standard Library
#include <iostream>
	using std::cout;
	using std::endl;
	using std::ostream;
#include <string>
	using std::string;

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                            Boost.Call_traits
#include <boost/call_traits.hpp>

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                          Expectation Checker
#include "Util/CK/CK.h"

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//		                                                	 Step 1
// Add expected results for '?'.
//
#if X_SOLVED >= 1
namespace boost_workshop { namespace call_traits { namespace step_1 {

void print(ostream& os, int v) {
	os << v << endl;
}

void print(ostream& os, double v) {
	os << v << endl;
}

void print(ostream& os, const string& v) {
	os << '"' << v << '"' << endl;
}

void tests() {
		int a = 17;
		double b = 3.25;
		string c = "hello";

CK_section(	"Several overloaded print functions .........................."	)
		std::ostringstream out;
		print(out, a);
		print(out, b);
		print(out, c);
				//////////////////////////////////
CK_compare(	out.str(),		"17"		"\n"   /*?:-2*/
					"3.25"		"\n"   /*?:-2*/
					"\"hello\""	"\n"   /*?:-2*/		)
				//////////////////////////////////
}

}}} // EONS ::boost_workshop::call_traits::step_1
#endif

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                                       Step 2
// Combine print functions into template.
// NOTE: no double-quotes printed for strings - see tests.
//
#if X_SOLVED >= 2

namespace boost_workshop { namespace call_traits { namespace step_2 {

template<class Value>						/*?=class Value*/
void print(ostream& os, Value v) {				/*?=Value v*/
	os << v << endl;					/*?*/
}

void tests() {
		int a = 17;
		double b = 3.25;
		string c = "hello";

CK_section(	"Template print function ....................................."	)
		std::ostringstream out;
		print(out, a);
		print(out, b);
		print(out, c);
				//////////////////////////////////
CK_compare(	out.str(),		"17"		"\n"
					"3.25"		"\n"
					"hello"		"\n"			)
				//////////////////////////////////
}

}}} // EONS ::boost_workshop::call_traits::step_2
#endif

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                                       Step 3
// Demonstrate call_traits<T>::param_type as used below will NOT work.
//
// Hint:
// Code of test-function must be DISABLED to continue with next step.
//
#if X_SOLVED >= 3

namespace boost_workshop { namespace call_traits { namespace step_3 {

template<class T>
void print(ostream& os, typename boost::call_traits<T>::param_type e) {
	cout << e << endl;
}

void tests() {
#if 1
CK_disable(	"Call traits cannot be resolved in this context .............." )
#else
		int a = 17;
		double b = 3.25;
		string c = "hello";
CK_section(	"Several overloaded print functions .........................."	)
		std::ostringstream out;
		print(out, a);
		print(out, b);
		print(out, c);
CK_compare(	out.str(),		"17"		"\n"
					"3.25"		"\n"
					"\"hello\""	"\n"			)
#endif								/*?:1*/
}

}}} // EONS ::boost_workshop::call_traits::step_3
#endif

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                                       Step 4
// Solve problem with a caller template
//
#if X_SOLVED >= 4

namespace boost_workshop { namespace call_traits { namespace step_4 {

template<class T>
class caller {
	typedef typename boost::call_traits<T>::param_type param_type;
public:
	static void print(ostream& os, param_type e);
};

template<class T>						/*?<*/
void caller<T>::print(ostream& os, typename boost::call_traits<T>::param_type e) {
	os << e << endl;
} 								/*?>*/

void tests() {
		int a = 17;
		double b = 3.25;
		string c = "hello";
CK_section(	"Solution with caller template class ........................."	)
		std::ostringstream out;
		caller<int>::print(out, a);
		caller<double>::print(out, b);
		caller<string>::print(out, c);
CK_compare(	out.str(),		"17"		"\n"
					"3.25"		"\n"
					"hello"		"\n"			)
}

}}} // EONS ::boost_workshop::call_traits::step_4

#endif

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                                       Step 5
// Add call helper to avoid redundant type argument
//
#if X_SOLVED >= 5

namespace boost_workshop { namespace call_traits { namespace step_5 {

template<class T>
class caller {
	typedef typename boost::call_traits<T>::param_type param_type;
public:
	static void print(ostream& os, param_type e);
};

template<class T>
void caller<T>::print(ostream& os, typename boost::call_traits<T>::param_type e) {
	os << e << endl;
} 

template<class T>
inline
void print_caller(ostream& os, T e) {
	return caller<T>::print(os, e);				/*?*/
}

void tests() {
		int a = 17;
		double b = 3.25;
		string c = "hello";
CK_section(	"Solution with caller template class and call helper ........."	)
		std::ostringstream out;
		print_caller(out, a);
		print_caller(out, b);
		print_caller(out, c);
CK_compare(	out.str(),		"17"		"\n"
					"3.25"		"\n"
					"hello"		"\n"			)
}

}}} // EONS ::boost_workshop::call_traits::step_5

#endif

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// 				   Call tests - nothing to change from here on.
//
int main() {
#if X_SOLVED >= 1
	boost_workshop::call_traits::step_1::tests();
#endif
#if X_SOLVED >= 2
	boost_workshop::call_traits::step_2::tests();
#endif
#if X_SOLVED >= 3
	boost_workshop::call_traits::step_3::tests();
#endif
#if X_SOLVED >= 4
	boost_workshop::call_traits::step_4::tests();
#endif
#if X_SOLVED >= 5
	boost_workshop::call_traits::step_5::tests();
#endif
}
