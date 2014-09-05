
#include <string>
	using namespace std;

#include <boost/regex.hpp>
	using boost::regex;
	using boost::smatch;
	using boost::regex_match;
	using boost::regex_replace;
	using boost::bad_expression;

#include <boost/lexical_cast.hpp>
	using boost::lexical_cast;

class CurrencyChecker {
	regex re;
	unsigned short decimal;
	unsigned long integral;
public:
	CurrencyChecker(const string &_re)
		: re(_re)
	{}
	bool check(const string &s) {
		smatch m;
		if (!regex_match(s, m, re))
			return false;
		const regex not_a_digit("[^0-9]");
		const string nothing;
		integral= lexical_cast<unsigned long>(
			regex_replace(string(m[1]), not_a_digit, nothing)
		);
		decimal= lexical_cast<unsigned short>(
			regex_replace(string(m[2]), not_a_digit, nothing)
		);
		return true;
	}
	unsigned long getIntegral() const { return integral; }
	unsigned short getDecimal() const { return decimal; }
};

#include <iostream>
#include "Util/CK/CK.h"

int main() {

	try {
		CurrencyChecker german("(\\d{1,3}(?:\\.\\d{3})*),(\\d{2})");

CK_section(	"German style (good format) ...."		)
CK_compare(	german.check("7,89")		, true		)
CK_compare(	german.getIntegral()		, 7		)
CK_compare(	german.getDecimal()		, 89		)

CK_compare(	german.check("67,89")		, true		)
CK_compare(	german.getIntegral()		, 67		)
CK_compare(	german.getDecimal()		, 89		)

CK_compare(	german.check("567,89")		, true		)
CK_compare(	german.getIntegral()		, 567		)
CK_compare(	german.getDecimal()		, 89		)

CK_compare(	german.check("4.567,89")	, true		)
CK_compare(	german.getIntegral()		, 4567		)
CK_compare(	german.getDecimal()		, 89		)

CK_compare(	german.check("1.234.567,89")	, true		)
CK_compare(	german.getIntegral()		, 1234567	)
CK_compare(	german.getDecimal()		, 89		)

CK_section(	"German style (bad format) ....."		)
CK_compare(	german.check("")		, false		)
CK_compare(	german.check("abc")		, false		)
CK_compare(	german.check("1")		, false		)
CK_compare(	german.check("12")		, false		)
CK_compare(	german.check("123")		, false		)
CK_compare(	german.check("1.23")		, false		)
CK_compare(	german.check("1,--")		, false		)
CK_compare(	german.check("1234,56")		, false		)
CK_compare(	german.check("1 234,56")	, false		)
CK_compare(	german.check("12.34,56")	, false		)
CK_compare(	german.check("A12.345,67")	, false		)
CK_compare(	german.check("12.345,6A")	, false		)

		CurrencyChecker other("(\\d{1,3}(?: \\d{3})*)\\.(\\d{2})");

CK_section(	"Other style (good format) ....."		)
CK_compare(	other.check("7.89")		, true		)
CK_compare(	other.getIntegral()		, 7		)
CK_compare(	other.getDecimal()		, 89		)

CK_compare(	other.check("67.89")		, true		)
CK_compare(	other.getIntegral()		, 67		)
CK_compare(	other.getDecimal()		, 89		)

CK_compare(	other.check("567.89")		, true		)
CK_compare(	other.getIntegral()		, 567		)
CK_compare(	other.getDecimal()		, 89		)

CK_compare(	other.check("4 567.89")		, true		)
CK_compare(	other.getIntegral()		, 4567		)
CK_compare(	other.getDecimal()		, 89		)

CK_compare(	other.check("1 234 567.89")	, true		)
CK_compare(	other.getIntegral()		, 1234567	)
CK_compare(	other.getDecimal()		, 89		)

CK_section(	"Other style (bad format) ......"		)
CK_compare(	other.check("")			, false		)
CK_compare(	other.check("abc")		, false		)
CK_compare(	other.check("1")		, false		)
CK_compare(	other.check("12")		, false		)
CK_compare(	other.check("123")		, false		)
CK_compare(	other.check(".23")		, false		)
CK_compare(	other.check("1.--")		, false		)
CK_compare(	other.check("1234.56")		, false		)
CK_compare(	other.check("1,234.56")		, false		)
CK_compare(	other.check("12 34.56")		, false		)
CK_compare(	other.check("A12 345.67")	, false		)
CK_compare(	other.check("12 345.6A")	, false		)

	}
	catch (bad_expression &ex) {
		cerr << ex.what() << endl;
		return 1;
	}

}
