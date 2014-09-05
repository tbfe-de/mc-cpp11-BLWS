/*
 * Count int-s, double-s, and strings- in input stream.
*/

#include <iostream>
#include <sstream>
#include <string>
	using namespace std;

#include <boost/algorithm/string.hpp>
	using boost::trim_left;
	using boost::trim_right;
	using boost::ends_with;
	using boost::replace_last;
	
bool process(istream &is, string &line) {
	line.clear();
	if (!getline(is, line))
		return false;
	while (ends_with(line, "\\")) {
		string cline;
		if (!getline(is, cline))
			break;
		replace_last(line, "\\", " ");
		trim_left(cline);
		line.append(cline);
	}
	trim_right(line);
	return true;
}

#include "Util/CK/CK.h"

int main() {

	string ln;
	{
CK_section(	"Empty Input ..................."			)
		istringstream in("");
CK_compare(	process(in, ln)			, false			)
	}

	{
CK_section(	"Simple Input .................."			)
		istringstream in(
			"one two"	"\n"
			"   three"	"\n"
			"four five  "	"\n"
			"six"		"\n"
		);
CK_compare(	process(in, ln)			, true			)
CK_compare(	ln				, string("one two")	)
CK_compare(	process(in, ln)			, true			)
CK_compare(	ln				, string("   three")	)
CK_compare(	process(in, ln)			, true			)
CK_compare(	ln				, string("four five")	)
CK_compare(	process(in, ln)			, true			)
CK_compare(	ln				, string("six")		)
CK_compare(	process(in, ln)			, false			)
	}

	{
CK_section(	"Complex Input ................."			)
		istringstream in(
			"one\\"		"\n"
			"two"		"\n"
			"   three"	"\n"
			"four\\"	"\n"
			"     five  "	"\n"
			"six\\ "	"\n"
		);
CK_compare(	process(in, ln)			, true			)
CK_compare(	ln				, string("one two")	)
CK_compare(	process(in, ln)			, true			)
CK_compare(	ln				, string("   three")	)
CK_compare(	process(in, ln)			, true			)
CK_compare(	ln				, string("four five")	)
CK_compare(	process(in, ln)			, true			)
CK_compare(	ln				, string("six\\")	)
CK_compare(	process(in, ln)			, false			)
	}
}
