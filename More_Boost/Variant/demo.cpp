#include "Util/CK/CK.h"

#include <boost/variant.hpp>

#include <string>
	using std::string;

int main() {
CK_section(	"Default Constructor ..........."			)
		boost::variant<int, double, string> a;
CK_compare(	boost::get<int>(a)		, 0			)

CK_section(	"Copy Constructor .............."			)
		boost::variant<int, double, string> b(22);
		boost::variant<int, double, string> c(string("hello"));
CK_compare(	boost::get<int>(a)		, 0			)
CK_compare(	boost::get<int>(b)		, 22			)
CK_compare(	boost::get<string>(c)		, string("hello")	)

CK_section(	"Type check ...................."			)
CK_compare(	a.type()			, typeid(int)		)
CK_compare(	b.type()			, typeid(int)		)
CK_compare(	c.type()       			, typeid(string)       	)

CK_section(	"Assignment ...................."			)
		a= 3.14;
CK_compare(	a.type().name()			, typeid(double).name()	)
CK_compare(	boost::get<double>(a)		, 3.14			)
}
