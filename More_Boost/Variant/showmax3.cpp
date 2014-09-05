#include <boost/variant.hpp>
#include <boost/ref.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#include <boost/lexical_cast.hpp>

class processing
		: private boost::reference_wrapper<int>
		, private boost::reference_wrapper<double>
		, private boost::reference_wrapper<string>
		, public boost::static_visitor<> {
public:
	processing(int &_imax, double &_dmax, string &_smax, ostream &_os)
		: boost::reference_wrapper<int>(_imax),
		  boost::reference_wrapper<double>(_dmax),
		  boost::reference_wrapper<string>(_smax),
		  os(_os)
	{}
	template<typename T>
	void operator()(const T &val) const {
		os << val;
		if (val == boost::reference_wrapper<T>::get())
			os << " <---";
		os << endl;
	}
private:
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
