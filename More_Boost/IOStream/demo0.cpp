#include "Util/CK/CK.h"

#include <boost/array.hpp>

int main() {

CK_section(	"Access ........................"		)
		boost::array<int, 3> a= {1, 4, 9};
CK_compare(	a[0]				, 1		)
CK_compare(	a[1]				, 4		)
CK_compare(	a[2]				, 9		)
CK_compare(	a.at(0)				, 1		)
CK_compare(	a.at(1)				, 4		)
CK_compare(	a.at(2)				, 9		)
CK_compare(	a.front()			, 1		)
CK_compare(	a.back()			, 9		)

CK_section(	"Properties ...................."		)
CK_compare(	a.size()			, 3		)

CK_section(	"Iterators ....................."		)
		boost::array<int, 3>::iterator it(a.begin());
CK_compare(	*it				, 1		)
CK_compare(	*++it				, 4		)
CK_compare(	*it++				, 4		)
CK_compare(	*it				, 9		)
CK_compare(	it 				, a.end()-1	)
CK_compare(	it == a.begin()			, false		)
		it -= 2;
CK_compare(	it == a.begin()			, true		)
		it += 3;
CK_compare(	it				, a.end()	)

CK_section(	"Comparisons ..................."		)
		boost::array<int, 3> b= {0, 0, 1};
		boost::array<int, 3> c= {1, 4, 9};
CK_compare(	a < b				, false		)
CK_compare(	b < c				, true		)
CK_compare(	a == b				, false		)
CK_compare(	a > c				, false		)
CK_compare(	a == c				, true		)
		a.swap(b);
CK_compare(	a == c				, false		)

}
