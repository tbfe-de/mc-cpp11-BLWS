#include <functional>
#include <iostream>
	using namespace std;

#include <boost/logic/tribool.hpp>
	using boost::logic::tribool;
	using boost::logic::indeterminate;
#include <boost/logic/tribool_io.hpp>
#include <boost/format.hpp>
	using boost::format;
	using boost::io::group;
#include <boost/lambda/lambda.hpp>
	using boost::lambda::_1;
	using boost::lambda::_2;
	using boost::lambda::ret;

const tribool all[]= { false, true, indeterminate };
const tribool *const all_begin= &all[0];
const tribool *const all_end= &all[3];

void show_op1(const char *opname, function<tribool(tribool)> op, ostream &os) {
	for (const tribool* rhs= all_begin; rhs < all_end; ++rhs) {
		os << format("%s %|-13| => %||\n")
			% opname
			% group(boolalpha, *rhs)
			% group(boolalpha, op(*rhs));
	}
}

void show_op2(const char *opname, function<tribool(tribool, tribool)> op, ostream &os) {
	for (const tribool* lhs= all_begin; lhs < all_end; ++lhs) {
		for (const tribool* rhs= all_begin; rhs < all_end; ++rhs) {
			os << format("%|-13| %s %|-13| => %||\n")
				% group(boolalpha, *lhs)
				% opname
				% group(boolalpha, *rhs)
				% group(boolalpha, op(*lhs, *rhs));
		}
	}
}

#include <sstream>

#include "Util/CK/CK.h"

int main() {

	{
CK_section("Negation ..........................."				)
		ostringstream os;
		show_op1("!", ret<tribool>(! _1), os);
CK_compare(	os.str(),
		"! false         => true"				"\n"
		"! true          => false"				"\n"
		"! indeterminate => indeterminate"			"\n"	)
	}

	{
CK_section("Logical AND ........................"				)
		ostringstream os;
		show_op2("&&", ret<tribool>(_1 && _2), os);
CK_compare(	os.str(),
		"false         && false         => false"		"\n"
		"false         && true          => false"		"\n"
		"false         && indeterminate => false"		"\n"
		"true          && false         => false"		"\n"
		"true          && true          => true"		"\n"
		"true          && indeterminate => indeterminate"	"\n"
		"indeterminate && false         => false"		"\n"
		"indeterminate && true          => indeterminate"	"\n"
		"indeterminate && indeterminate => indeterminate"	"\n"	)
	}

	{
CK_section("Logical OR ........................."				)
		ostringstream os;
		show_op2("||", ret<tribool>(_1 || _2), os);
CK_compare(	os.str(),
		"false         || false         => false"		"\n"
		"false         || true          => true"		"\n"
		"false         || indeterminate => indeterminate"	"\n"
		"true          || false         => true"		"\n"
		"true          || true          => true"		"\n"
		"true          || indeterminate => true"		"\n"
		"indeterminate || false         => indeterminate"	"\n"
		"indeterminate || true          => true"		"\n"
		"indeterminate || indeterminate => indeterminate"	"\n"	)
	}

	{
CK_section("Equality ..........................."				)
		ostringstream os;
		show_op2("==", ret<tribool>(_1 == _2), os);
CK_compare(	os.str(),
		"false         == false         => true"		"\n"
		"false         == true          => false"		"\n"
		"false         == indeterminate => indeterminate"	"\n"
		"true          == false         => false"		"\n"
		"true          == true          => true"		"\n"
		"true          == indeterminate => indeterminate"	"\n"
		"indeterminate == false         => indeterminate"	"\n"
		"indeterminate == true          => indeterminate"	"\n"
		"indeterminate == indeterminate => indeterminate"	"\n"	)
	}

	{
CK_section("Unequality ........................."				)
		ostringstream os;
		show_op2("!=", ret<tribool>(_1 != _2), os);
CK_compare(	os.str(),
		"false         != false         => false"		"\n"
		"false         != true          => true"		"\n"
		"false         != indeterminate => indeterminate"	"\n"
		"true          != false         => true"		"\n"
		"true          != true          => false"		"\n"
		"true          != indeterminate => indeterminate"	"\n"
		"indeterminate != false         => indeterminate"	"\n"
		"indeterminate != true          => indeterminate"	"\n"
		"indeterminate != indeterminate => indeterminate"	"\n"	)
	}

}

