/*
 ==============================================================================
 Read white-space separated words from standard input into a vector of "any"-s
 and determine if they can be interpreted as integral numbers, floating point
 numbers or something else (plain string). When all input is consumed, print
 the vector content and mark the maximum value for each of the possibilities.
 ==============================================================================
*/

// ----------------------------------------------------------------------------
//                                                    From Standard C++ Library
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// ----------------------------------------------------------------------------
//                                                          From Boost-Platform
#include <boost/any.hpp>
#include <boost/lexical_cast.hpp>

void process(istream &is, ostream &os) {
	vector<boost::any> v;
	string w;
	int imax= 0;
	double dmax= 0.0;
	string smax= "";
	while (is >> w) {
		try {
			const int ival= boost::lexical_cast<int>(w);
			v.push_back(ival);
			if (ival > imax) imax= ival;
			continue;
		}
		catch (boost::bad_lexical_cast &ignored) {}
		try {
			const double dval= boost::lexical_cast<double>(w);
			v.push_back(dval);
			if (dval > dmax) dmax= dval;
			continue;
		}
		catch (boost::bad_lexical_cast &ignored) {}
		try {
			const string sval= boost::lexical_cast<string>(w);
			v.push_back(sval);
			if (sval > smax) smax= sval;
			continue;
		}
		catch (boost::bad_lexical_cast &ignored) {}
		
	}
	while (!v.empty()) {
		if (v.back().type() == typeid(int)) {
			const int ival= boost::any_cast<int>(v.back());
			os << ival;
			if (ival == imax)
				os << " <---";
			os << endl;
		}
		if (v.back().type() == typeid(double)) {
			const double dval= boost::any_cast<double>(v.back());
			os << dval;
			if (dval == dmax)
				os << " <---";
			os << endl;
		}
		if (v.back().type() == typeid(string)) {
			const string sval= boost::any_cast<string>(v.back());
			os << sval;
			if (sval == smax)
				os << " <---";
			os << endl;
		}
		v.pop_back();
	}
}

#include "Util/CK/CK.h"

int main() {
#ifdef INTERACTIVE
	process(cin, cout);
#else

	{
CK_section(	"Empty Input ..................."			)
		istringstream in("");
		ostringstream out;
		process(in, out);
CK_compare(	out.str(), ""						)
	}

	{
CK_section(	"int-only Input ................"			)
		istringstream in("1 3 1 2");
		ostringstream out;
		process(in, out);
CK_compare(	out.str(),
				"2"			"\n"
				"1"			"\n"
				"3 <---"		"\n"
				"1"			"\n"		)
	}

	{
CK_section(	"double-only Input ............."			)
		istringstream in("2.2 0.3");
		ostringstream out;
		process(in, out);
CK_compare(	out.str(),
				"0.3"			"\n"
				"2.2 <---"		"\n"		)
	}

	{
CK_section(	"string-only Input ............."			)
		istringstream in("hello world");
		ostringstream out;
		process(in, out);
CK_compare(	out.str(),
				"world <---"		"\n"
				"hello"			"\n"		)
	}

	{
CK_section(	"Mixed Input ..................."			)
		istringstream in("1 2.2 hello 3 1 2 0.3 world");
		ostringstream out;
		process(in, out);
CK_compare(	out.str(),
				"world <---"		"\n"
				"0.3"			"\n"
				"2"			"\n"
				"1"			"\n"
				"3 <---"		"\n"
				"hello"			"\n"
				"2.2 <---"		"\n"
				"1"			"\n"		)
	}
#endif
}

