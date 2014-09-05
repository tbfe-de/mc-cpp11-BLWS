#include <boost/variant.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#include <boost/lexical_cast.hpp>

struct processing : boost::static_visitor<> {
	processing(int &_imax, double &_dmax, string &_smax, ostream &_os)
		: imax(_imax), dmax(_dmax), smax(_smax), os(_os)
	 {}
	void operator()(const int &ival) const {
		os << ival;
		if (ival == imax)
			os << " <---";
		os << endl;
	}
	void operator()(const double &dval) const {
		os << dval;
		if (dval == dmax)
			os << " <---";
		os << endl;
	}
	void operator()(const string &sval) const {
		os << sval;
		if (sval == smax)
			os << " <---";
		os << endl;
	}
private:
	const int &imax;
	const double &dmax;
	const string &smax;
	ostream &os;
};

void process(istream &is, ostream &os) {
	typedef boost::variant<int, double, string> ids_t;
	vector<ids_t> v;
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
		boost::apply_visitor(processing(imax, dmax, smax, os), v.back());
		v.pop_back();
	}
}

#include "Util/CK/CK.h"

int main() {

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
}
