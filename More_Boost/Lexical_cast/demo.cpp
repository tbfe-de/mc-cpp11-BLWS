/*
 * Count int-s, double-s, and strings- in input stream.
*/

#include <iostream>
#include <sstream>
#include <string>

#include <boost/lexical_cast.hpp>

using namespace std;

void process(istream &is, ostream &os) {
	int icount= 0;
	int scount= 0;
	int dcount= 0;
	string w;
	while (is >> w) {
		try {
			boost::lexical_cast<int>(w);
			++icount;
			continue;
		}
		catch (boost::bad_lexical_cast &ignored) {}
		try {
			boost::lexical_cast<double>(w);
			++dcount;
			continue;
		}
		catch (boost::bad_lexical_cast &ignored) {}
		try {
			boost::lexical_cast<string>(w);
			++scount;
			continue;
		}
		catch (boost::bad_lexical_cast &ignored) {}
		
	}
	os << "int-s: " << icount << endl;
	os << "double-s: " << dcount << endl;
	os << "string-s: " << scount << endl;
}

#include "Util/CK/CK.h"

int main() {
	/////////////////////////////////////////////////////////////////
	{
CK_section(	"Empty Input ..................."			)
		istringstream in("");
		ostringstream out;
		process(in, out);
CK_compare(	out.str(),
				"int-s: 0"		"\n"
				"double-s: 0"		"\n"
				"string-s: 0"		"\n"		)
	}
	/////////////////////////////////////////////////////////////////
	{
CK_section(	"int-only Input ................"			)
		istringstream in("1 3 1 2");
		ostringstream out;
		process(in, out);
CK_compare(	out.str(),
				"int-s: 4"		"\n"
				"double-s: 0"		"\n"
				"string-s: 0"		"\n"		)
	}
	/////////////////////////////////////////////////////////////////
	{
CK_section(	"double-only Input ............."			)
		istringstream in("2.2 0.3");
		ostringstream out;
		process(in, out);
CK_compare(	out.str(),
				"int-s: 0"		"\n"
				"double-s: 2"		"\n"
				"string-s: 0"		"\n"		)
	}
	/////////////////////////////////////////////////////////////////
	{
CK_section(	"string-only Input ............."			)
		istringstream in("hello world");
		ostringstream out;
		process(in, out);
CK_compare(	out.str(),
				"int-s: 0"		"\n"
				"double-s: 0"		"\n"
				"string-s: 2"		"\n"		)
	}
	/////////////////////////////////////////////////////////////////
	{
CK_section(	"Mixed Input ..................."			)
		istringstream in("1 2.2 hello 3 1 2 0.3 world");
		ostringstream out;
		process(in, out);
CK_compare(	out.str(),
				"int-s: 4"		"\n"
				"double-s: 2"		"\n"
				"string-s: 2"		"\n"		)
	}
	/////////////////////////////////////////////////////////////////
}
