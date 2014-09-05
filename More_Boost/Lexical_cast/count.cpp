/*
 * Count int-s, double-s, and strings- in input stream.
*/

#include <iostream>
#include <sstream>
#include <string>
	using namespace std;

#include <boost/lexical_cast.hpp>
	using boost::lexical_cast;
	using boost::bad_lexical_cast;

template <typename TypeToConvertIn>

bool check(const string& stringToConvert) {
	try {
		static_cast<void>(
			// only need to check content, the result not used!!
			lexical_cast<TypeToConvertIn>(stringToConvert)
		);
		return true;
	}
	catch (bad_lexical_cast &) {
		return false;
	}
}

void process(istream &is, string &result) {
	int icount= 0;
	int scount= 0;
	int dcount= 0;
	string w;
	while (is >> w) {
		if (check<int>(w))
			++icount;
		else if (check<double>(w))
			++dcount;
		else
			++scount;
		
	}
	result.clear();
	result.append("int-s: " + lexical_cast<string>(icount) + "\n");
	result.append("double-s: " + lexical_cast<string>(dcount) + "\n");
	result.append("string-s: " + lexical_cast<string>(scount) + "\n");
}

#include "Util/CK/CK.h"

int main() {

	{
CK_section(	"Empty Input ..................."			)
		istringstream in("");
		string out;
		process(in, out);
CK_compare(	out,
				"int-s: 0"		"\n"
				"double-s: 0"		"\n"
				"string-s: 0"		"\n"		)
	}

	{
CK_section(	"Mixed Input ..................."			)
		istringstream in("1 2.2 hello 3 1 2 0.3");
		string out;
		process(in, out);
CK_compare(	out,
				"int-s: 4"		"\n"
				"double-s: 2"		"\n"
				"string-s: 1"		"\n"		)
	}
}
