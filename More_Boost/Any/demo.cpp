/* Exercise: Any/demo.cpp
 * ============================================================================
 * Boost Library Workshop -- Demo Program for 'Boost.Any'
 * Supplied by: Technische Beratung fuer EDV, D-64380 Rossdorf, Germany
 * Author and Copyright (2011): Dipl.-Ing. Martin Weitzel (www.tbfe.de)
 * ============================================================================
*/
#define	X_SOLVED    4							  /*?#*/

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                             Standard Library
#include <string>
	using std::string;

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                                    Boost.Any
#include <boost/any.hpp>

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                          Expectation Checker
#include "Util/CK/CK.h"

int main() {
		boost::any a;
		boost::any b(22);
		boost::any c(string("hello"));
#if X_SOLVED >= 1
	{ // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::	
CK_section(	"Copy Constructor ...................................."	)
CK_compare(	boost::any_cast<int>(b)		, 22			) /*?:-2*/
CK_compare(	boost::any_cast<string>(c)	, string("hello")	) /*?:-2*/
	} // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#endif
#if X_SOLVED >= 2
	{ // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
CK_section(	"Content check ......................................."	)
CK_compare(	a.empty()			, true			) /*?:-2*/
CK_compare(	b.empty()			, false			) /*?:-2*/
CK_compare(	c.empty()			, false			) /*?:-2*/
	} // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#endif
#if X_SOLVED >= 3
	{ // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
CK_section(	"Type check .........................................."	) /*?:-2*/
CK_compare(	b.type()			, typeid(int)		) /*?:-2*/
CK_compare(	c.type()			, typeid(string)	) /*?:-2*/
	} // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#endif
#if X_SOLVED >= 4
	{ // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
CK_section(	"Assignment .........................................."	)
		a= 3.14;
CK_compare(	a.empty()			, false			) /*?:-2*/
CK_compare(	a.type()			, typeid(double)	) /*?:-2*/
CK_compare(	boost::any_cast<string>(a)	, "3.14"		) /*?:-2*/
	} // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#endif
}
