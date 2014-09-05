/* Exercise: Array/demo.cpp
 * ============================================================================
 * Boost Library Workshop -- Demo Program for 'Boost.Array'
 * Supplied by: Technische Beratung fuer EDV, D-64380 Rossdorf, Germany
 * Author and Copyright (2011): Dipl.-Ing. Martin Weitzel (www.tbfe.de)
 * ============================================================================
*/
#define	X_SOLVED    1							  /*?#*/

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                                  Boost.Array
#include <boost/array.hpp>

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                          Expectation Checker
#include "Util/CK/CK.h"

int main() {

		boost::array<int, 3> a= {{ 1, 4, 9 }};
#if X_SOLVED >= 1
	{ // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
CK_section(	"Access .............................................."	)
CK_compare(	a[0]				, 1			) /*?:-2*/
CK_compare(	a[1]				, 4			) /*?:-2*/
CK_compare(	a[2]				, 9			) /*?:-2*/
CK_compare(	a.at(0)				, 1			) /*?:-2*/
CK_compare(	a.at(1)				, 4			) /*?:-2*/
CK_compare(	a.at(2)				, 9			) /*?:-2*/
CK_compare(	a.front()			, 1			) /*?:-2*/
CK_compare(	a.back()			, 9			) /*?:-2*/
	} // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#endif
#if X_SOLVED >= 2
	{ // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
CK_section(	"Properties .........................................."	)
CK_compare(	a.size()			, 3			) /*?:-2*/
	} // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#endif
#if X_SOLVED >= 3
	{ // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
CK_section(	"Iterators ..........................................."	) /*?:-2*/
		boost::array<int, 3>::iterator it(a.begin());
CK_compare(	*it				, 1			) /*?:-2*/
CK_compare(	*++it				, 4			) /*?:-2*/
CK_compare(	*it++				, 4			) /*?:-2*/
CK_compare(	*it				, 9			) /*?:-2*/
CK_compare(	it 				, a.end()-1		) /*?:-2*/
CK_compare(	it == a.begin()			, false			) /*?:-2*/
		it -= 2;
CK_compare(	it == a.begin()			, true			) /*?:-2*/
		it += 3;
CK_compare(	it				, a.end()		) /*?:-2*/
	} // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#endif
#if X_SOLVED >= 4
	{ // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
CK_section(	"Comparisons ........................................."	) /*?:-2*/
		boost::array<int, 3> b= {{ 0, 0, 1 }};
		boost::array<int, 3> c= {{ 1, 4, 9 }};
CK_compare(	a < b				, false			) /*?:-2*/
CK_compare(	b < c				, true			) /*?:-2*/
CK_compare(	a == b				, false			) /*?:-2*/
CK_compare(	a > c				, false			) /*?:-2*/
CK_compare(	a == c				, true			) /*?:-2*/
		a.swap(b);
CK_compare(	a == c				, false			) /*?:-2*/
	} // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#endif

}
