#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;

#include <iostream>
	using std::istream;
#include <iterator>
	using std::istream_iterator;
#include <sstream>
	using std::istringstream;
#include <string>
	using std::string;
#include <vector>
	using std::vector;

bool parseOneSingleInt(const string& input) {
	string::const_iterator currentParsePosition(input.begin());
	const bool inputIsWellformed =
		qi::parse(
			currentParsePosition, input.end(),

			// begin of grammar (no semantic actions)
			// ------------------------------------------------------------
			(
			    qi::int_
			)
			// ------------------------------------------------------------
			// end of grammar (no semantic actions)

		)  // end of call to qi::parse
	; // end of result assignment

	return inputIsWellformed
            && currentParsePosition == input.end();
}

bool parseOneSingleDouble(const string& input) {
	// used in grammar:
	using qi::double_;
	using ascii::space;

	string::const_iterator currentParsePosition(input.begin());
	const bool inputIsWellformed(
		qi::phrase_parse(
			currentParsePosition, input.end(),

			// begin of grammar (no semantic actions)
			// ------------------------------------------------------------
			(
			    double_
			),
			// ------------------------------------------------------------
			// end of grammar (no semantic actions)

			space

		)  // end of call to qi::parse
	); // end of result assignment

	return inputIsWellformed
            && currentParsePosition == input.end();
}

bool oneSingleDoubleWithStoring(const string& input, double& v) {
	// used in grammar:
	using qi::double_;
	using qi::_1;
	using ascii::space;
	using phoenix::ref;

	string::const_iterator currentParsePosition(input.begin());
	const bool inputIsWellformed(
		qi::phrase_parse(
			currentParsePosition, input.end(),

			// begin of grammar (with semantic action)
			// ------------------------------------------------------------
			(
			    double_[ref(v) = _1]
			),
			// ------------------------------------------------------------
			// end of grammar (with semantic action)

			space

		)  // end of call to qi::parse
	); // end of result assignment

	return inputIsWellformed
            && currentParsePosition == input.end();
}

bool parseTwoInts_csep(const string& input) {
	// used in grammar:
	using qi::int_;
	using ascii::space;

	string::const_iterator currentParsePosition(input.begin());
	const bool inputIsWellformed(
		qi::phrase_parse(
			currentParsePosition, input.end(),

			// begin of grammar (no semantic actions)
			// ------------------------------------------------------------
			(
			    int_ >> ',' >> int_
			),
			// ------------------------------------------------------------
			// end of grammar (no semantic actions)

			space

		)  // end of call to qi::parse
	); // end of result assignment

	return inputIsWellformed
            && currentParsePosition == input.end();
}

bool parseTimestamp(const string& input) {
	// used in grammar:
	using qi::int_;
	using ascii::digit;

	string::const_iterator currentParsePosition(input.begin());
	const bool inputIsWellformed(
		qi::parse(
			currentParsePosition, input.end(),

			// begin of grammar (no semantic actions)
			// ------------------------------------------------------------
			(
			    digit >> digit >> ':' >> digit >> digit
			)
			// ------------------------------------------------------------
			// end of grammar (no semantic actions)

		)  // end of call to qi::parse
	); // end of result assignment

	return inputIsWellformed
            && currentParsePosition == input.end();
}

bool parseOptionalNumber(const string& input) {
	// used in grammar:
	using qi::double_;
	using ascii::space;

	string::const_iterator currentParsePosition(input.begin());
	const bool inputIsWellformed(
		qi::phrase_parse(
			currentParsePosition, input.end(),

			// begin of grammar (no semantic actions)
			// ------------------------------------------------------------
			(
			    - double_
			 // ^--------- optional (0- oder 1-mal)
			),
			// ------------------------------------------------------------
			// end of grammar (no semantic actions)

			space

		)  // end of call to qi::parse
	); // end of result assignment

	return inputIsWellformed
            && currentParsePosition == input.end();
}

bool parseNonEmptyList(const string& input) {
	// used in grammar:
	using qi::double_;
	using ascii::space;

	string::const_iterator currentParsePosition(input.begin());
	const bool inputIsWellformed(
		qi::phrase_parse(
			currentParsePosition, input.end(),

			// begin of grammar (no semantic actions)
			// ------------------------------------------------------------
			(
			    + double_
			 // ^--------- non-empty repetition (1-mal oder beliebig oft)
			),
			// ------------------------------------------------------------
			// end of grammar (no semantic actions)

			space

		)  // end of call to qi::parse
	); // end of result assignment

	return inputIsWellformed
            && currentParsePosition == input.end();
}

bool parseMaybeEmptyList(const string& input) {
	// used in grammar:
	using qi::double_;
	using ascii::space;

	string::const_iterator currentParsePosition(input.begin());
	const bool inputIsWellformed(
		qi::phrase_parse(
			currentParsePosition, input.end(),

			// begin of grammar (no semantic actions)
			// ------------------------------------------------------------
			(
			    * double_
			 // ^--------- possibly empty repetition (0-mal oder beliebig oft)
			),
			// ------------------------------------------------------------
			// end of grammar (no semantic actions)

			space

		)  // end of call to qi::parse
	); // end of result assignment

	return inputIsWellformed
            && currentParsePosition == input.end();
}

bool parseNonEmptyList_csep(const string& input) {
	// used in grammar:
	using qi::double_;
	using ascii::space;

	string::const_iterator currentParsePosition(input.begin());
	const bool inputIsWellformed(
		qi::phrase_parse(
			currentParsePosition, input.end(),

			// begin of grammar (no semantic actions)
			// ------------------------------------------------------------
			(
			    double_ >> *( ',' >> double_ )
			),
			// ------------------------------------------------------------
			// end of grammar (no semantic actions)

			space

		)  // end of call to qi::parse
	); // end of result assignment

	return inputIsWellformed
            && currentParsePosition == input.end();
}

bool parseMaybeEmptyList_csep(const string& input) {
	// used in grammar:
	using qi::double_;
	using ascii::space;

	string::const_iterator currentParsePosition(input.begin());
	const bool inputIsWellformed(
		qi::phrase_parse(
			currentParsePosition, input.end(),

			// begin of grammar (no semantic actions)
			// ------------------------------------------------------------
			(
			    - ( double_ >> *( ',' >> double_ ) )
			),
			// ------------------------------------------------------------
			// end of grammar (no semantic actions)

			space

		)  // end of call to qi::parse
	); // end of result assignment

	return inputIsWellformed
            && currentParsePosition == input.end();
}

bool listWithStoring_csep(const string& input, vector<int>& result) {
	// used in grammar:
	using qi::int_;
	using qi::_1;
	using ascii::space;
	using phoenix::push_back;

	string::const_iterator currentParsePosition(input.begin());
	const bool inputIsWellformed(
		qi::phrase_parse(
			currentParsePosition, input.end(),

			// begin of grammar (with semantic actions)
			// ------------------------------------------------------------
			(
			    int_[push_back(phoenix::ref(result), _1)]
				>> *( ',' >> int_[push_back(phoenix::ref(result), _1)])
			),
			// ------------------------------------------------------------
			// end of grammar (with semantic actions)

			space

		)  // end of call to qi::parse
	); // end of result assignment

	return inputIsWellformed
            && currentParsePosition == input.end();
}

#include "Util/CK/CK.h"

#include <string>
	using std::string;

int main() {
	{ // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
CK_section(	"One single integer ...................."		)
CK_compare(	parseOneSingleInt("33")			, true         	)
CK_compare(	parseOneSingleInt("44")			, true         	)
CK_compare(	parseOneSingleInt("-3")			, true         	)
CK_compare(	parseOneSingleInt("+4")			, true         	)
CK_compare(	parseOneSingleInt(" 5")			, false        	)
CK_compare(	parseOneSingleInt("4 ")			, false       	)
CK_compare(	parseOneSingleInt("4a")			, false        	)
CK_compare(	parseOneSingleInt("zz")			, false        	)
CK_compare(	parseOneSingleInt("")			, false        	)
	} // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

	{ // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
CK_section(	"One single double ....................."		)
CK_compare(	parseOneSingleDouble("123.45")		, true         	)
CK_compare(	parseOneSingleDouble("123")		, true         	)
CK_compare(	parseOneSingleDouble(".45")		, true         	)
CK_compare(	parseOneSingleDouble("4 ")		, true        	)
CK_compare(	parseOneSingleDouble(" .5")		, true         	)
CK_compare(	parseOneSingleDouble("  4.5  ")		, true        	)
CK_compare(	parseOneSingleDouble(" -4.5 ")		, true        	)
CK_compare(	parseOneSingleDouble(" +4.5 ")		, true        	)
CK_compare(	parseOneSingleDouble(" 1e4 ")		, true        	)
CK_compare(	parseOneSingleDouble(" 1e+4")		, true        	)
CK_compare(	parseOneSingleDouble(" 1e-4")		, true        	)
CK_compare(	parseOneSingleDouble("-1e+4")		, true        	)
CK_compare(	parseOneSingleDouble("+1e-4")		, true        	)
CK_compare(	parseOneSingleDouble("0004")		, true        	)
CK_compare(	parseOneSingleDouble("1ee4")		, false       	)
CK_compare(	parseOneSingleDouble("++1")		, false      	)
CK_compare(	parseOneSingleDouble("-1-")		, false        	)
CK_compare(	parseOneSingleDouble("")		, false        	)
	} // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

	{ // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		double v;
CK_section(	"One single double (with storing) ......"		)
CK_compare(	oneSingleDoubleWithStoring("123.45", v)	, true         	)
CK_compare(	v					, 123.45	)
CK_compare(	oneSingleDoubleWithStoring("123", v)	, true         	)
CK_compare(	v					, 123.0 	)
CK_compare(	oneSingleDoubleWithStoring(".45", v)	, true         	)
CK_compare(	v					, 0.45    	)
CK_compare(	oneSingleDoubleWithStoring("4 ", v)	, true        	)
CK_compare(	v					, 4.0    	)
CK_compare(	oneSingleDoubleWithStoring(" .5", v)	, true         	)
CK_compare(	v					, 0.5    	)
CK_compare(	oneSingleDoubleWithStoring(" 4.5  ", v)	, true        	)
CK_compare(	v					, 4.5    	)
CK_compare(	oneSingleDoubleWithStoring(" -4.5 ", v)	, true        	)
CK_compare(	v					, -4.5    	)
CK_compare(	oneSingleDoubleWithStoring(" +4.5 ", v)	, true        	)
CK_compare(	v					, 4.5    	)
CK_compare(	oneSingleDoubleWithStoring(" 1e4 ", v)	, true        	)
CK_compare(	v					, 10.0*1000    	)
CK_compare(	oneSingleDoubleWithStoring(" 1e+4", v)	, true        	)
CK_compare(	v					, 10.0*1000    	)
CK_compare(	oneSingleDoubleWithStoring(" 1e-4", v)	, true        	)
CK_compare(	v					, 1.0/(10*1000)	)
CK_compare(	oneSingleDoubleWithStoring("-1e+4", v)	, true        	)
CK_compare(	v					, -10.0*1000   	)
CK_compare(	oneSingleDoubleWithStoring("+1e-4", v)	, true        	)
CK_compare(	v					, 1.0/(10*1000)	)
CK_compare(	oneSingleDoubleWithStoring("0004", v)	, true        	)
CK_compare(	v					, 4.0	  	)
CK_compare(	oneSingleDoubleWithStoring("0014", v)	, true        	)
CK_compare(	v					, 14.0	  	)
	} // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

	{ // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
CK_section(	"Two comma separated integers .........."		)
CK_compare(	parseTwoInts_csep("3,4")		, true         	)
CK_compare(	parseTwoInts_csep(" 3 , 4 ")		, true         	)
CK_compare(	parseTwoInts_csep(" 3,4 ")		, true         	)
CK_compare(	parseTwoInts_csep("3,")			, false        	)
CK_compare(	parseTwoInts_csep(",4")			, false        	)
CK_compare(	parseTwoInts_csep(",")			, false        	)
CK_compare(	parseTwoInts_csep("")			, false        	)
	} // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

	{ // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
CK_section(	"hh:mm time stamp (no spaces) .........."		)
CK_compare(	parseTimestamp("12:31")			, true         	)
CK_compare(	parseTimestamp("00:00")			, true         	)
CK_compare(	parseTimestamp("15:59")			, true         	)
CK_compare(	parseTimestamp("16:00")			, true         	)
CK_compare(	parseTimestamp("15:60")			, true		)
CK_compare(	parseTimestamp(" 15:60")		, false        	)
CK_compare(	parseTimestamp("12: 2")			, false        	)
CK_compare(	parseTimestamp("4:5")			, false        	)
CK_compare(	parseTimestamp(":")			, false        	)
CK_compare(	parseTimestamp("")			, false        	)
	} // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

	{ // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
CK_section(	"Optional single double value .........."		)
CK_compare(	parseOptionalNumber("")			, true         	)
CK_compare(	parseOptionalNumber("3.14")		, true         	)
CK_compare(	parseOptionalNumber("3")		, true         	)
CK_compare(	parseOptionalNumber("3 14")		, false        	)
	} // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

	{ // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
CK_section(	"Non-empty list of double values ......."		)
CK_compare(	parseNonEmptyList("")			, false        	)
CK_compare(	parseNonEmptyList("3.14")		, true         	)
CK_compare(	parseNonEmptyList("3")			, true         	)
CK_compare(	parseNonEmptyList("3 14")		, true        	)
	} // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

	{ // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
CK_section(	"Maybe empty list of double values ....."		)
CK_compare(	parseMaybeEmptyList("")			, true        	)
CK_compare(	parseMaybeEmptyList("3.14")		, true         	)
CK_compare(	parseMaybeEmptyList("3")		, true         	)
CK_compare(	parseMaybeEmptyList("3 14")		, true        	)
	} // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

	{ // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
CK_section(	"Comma separated non-empty list ........"		)
CK_compare(	parseNonEmptyList_csep("3.14 , 15, 16")	, true         	)
CK_compare(	parseNonEmptyList_csep("3.14,15")	, true         	)
CK_compare(	parseNonEmptyList_csep("3.14")		, true         	)
CK_compare(	parseNonEmptyList_csep("")		, false        	)
CK_compare(	parseNonEmptyList_csep("  ")		, false        	)
CK_compare(	parseNonEmptyList_csep("zzz")		, false        	)
	} // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

	{ // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
CK_section(	"Comma separated maybe empty list ......"		)
CK_compare(	parseMaybeEmptyList_csep("3.14 , 15")	, true         	)
CK_compare(	parseMaybeEmptyList_csep("3.14")	, true         	)
CK_compare(	parseMaybeEmptyList_csep("")		, true        	)
CK_compare(	parseMaybeEmptyList_csep("  ")		, true        	)
CK_compare(	parseMaybeEmptyList_csep("zzz")		, false        	)
	} // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

	{ // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
CK_section(	"Comma separated list with storing ....."		)
		vector<int> out;
CK_compare(	listWithStoring_csep("33", out)		, true         	)
CK_compare(	out.size()				, 1		)
CK_compare(	out.at(0)				, 33		)
		out.clear();
CK_compare(	listWithStoring_csep("33, 44", out)	, true         	)
CK_compare(	out.size()				, 2		)
CK_compare(	out.at(0)				, 33		)
CK_compare(	out.at(1)				, 44		)
		out.clear();
CK_compare(	listWithStoring_csep("02,-4,+555", out)	, true         	)
CK_compare(	out.size()				, 3		)
CK_compare(	out.at(0)				, 2		)
CK_compare(	out.at(1)				, -4		)
CK_compare(	out.at(2)				, 555		)
		out.clear();
CK_compare(	listWithStoring_csep("", out)		, false        	)
CK_compare(	listWithStoring_csep("33,zzz", out)	, false        	)
	} // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
}

