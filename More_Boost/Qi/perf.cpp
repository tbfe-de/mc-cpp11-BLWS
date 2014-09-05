#include <cassert>
#include <string>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/qi.hpp>

#include "Util/CxTime/CXTIME.h"

int main() {
	using boost::spirit::qi::parse;
	using boost::spirit::qi::double_;
	using boost::spirit::qi::long_;
	using boost::spirit::qi::_1;
	using boost::phoenix::ref;

	const std::string si("7654221");
	const std::string sd("76542.1");

	CXTIME("Conversion of long via 'std::atol'",
			long n;
		,
			n = atol(si.c_str());
		,
			assert(n == 7654221);
		,
	)

	CXTIME("Conversion of long via 'boost::spirit::qi'",
			long n;
		,
			parse(si.begin(), si.end(), long_[ref(n) = _1]);
		,
			assert(n == 7654221);
		,
	)

	CXTIME("Conversion of double via 'std::atof'",
			double n;
		,
			n = atof(sd.c_str());
		,
			assert(n == 76542.1);
		,
	)

	CXTIME("Conversion of double via 'boost::spirit::qi'",
			double n;
		,
			parse(sd.begin(), sd.end(), double_[ref(n) = _1]);
		,
			assert(n == 76542.1);
		,
	)
}
