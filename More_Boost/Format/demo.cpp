/*
 * Count int-s, double-s, and strings- in input stream.
*/

#include <iostream>
#include <sstream>
#include <string>
	using namespace std;

#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>
	using boost::format;
	using boost::str;

template <typename TypeToConvertIn>
bool check(const string& stringToConvert) {
	try {
		static_cast<void>(
			// only need to check content, the result not used!!
			boost::lexical_cast<TypeToConvertIn>(stringToConvert)
		);
		return true;
	}
	catch (boost::bad_lexical_cast &) {
		return false;
	}
}

string process(string in, const char *out) {
	int icount= 0;
	int scount= 0;
	int dcount= 0;
	istringstream is(in);
	string w;
	while (is >> w) {
		if (check<int>(w))
			++icount;
		else if (check<double>(w))
			++dcount;
		else
			++scount;
		
	}
	return str(format(out) % icount % dcount % scount);
}

#include "Util/CK/CK.h"

int main() {

	{
CK_section(	"Mixed Input ..................."			)
		const string in("1 2.2 hello 3 1 2 0.3");
CK_compare(	process(in,
		// output format
			"icount=%d, dcount=%d, scount=%d"),
		// expected result
			"icount=4, dcount=2, scount=1"			)

CK_compare(	process(in,
		// output format
			"int-s: %d"		"\n"
			"double-s: %d"		"\n"
			"string-s: %d"		"\n"),
		// expected result
			"int-s: 4"		"\n"
			"double-s: 2"		"\n"
			"string-s: 1"		"\n"			)

CK_compare(	process(in,
		// output format
			"int-s:    %03d"	"\n"
			"double-s: %03d"	"\n"
			"string-s: %03d"	"\n"),
		// expected result
			"int-s:    004"		"\n"
			"double-s: 002"		"\n"
			"string-s: 001"		"\n"			)

CK_compare(	process(in,
		// output format
			"string-s: %3$d"	"\n"
			"double-s: %2$d"	"\n"
			"int-s: %1$d"		"\n"),
		// expected result
			"string-s: 1"		"\n"		
			"double-s: 2"		"\n"
			"int-s: 4"		"\n"			)
	}

}
