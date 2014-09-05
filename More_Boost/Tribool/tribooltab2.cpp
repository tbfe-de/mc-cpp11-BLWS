#include <functional>
#include <iostream>
	using namespace std;

	using std::function;
#include <boost/logic/tribool.hpp>
	using boost::logic::tribool;
	using boost::logic::indeterminate;
#include <boost/logic/tribool_io.hpp>
#include <boost/format.hpp>
	using boost::format;
	using boost::io::group;

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

tribool tribool_NOT(tribool rhs) { return !rhs; }
tribool tribool_AND(tribool lhs, tribool rhs) { return lhs && rhs; }
tribool tribool_OR(tribool lhs, tribool rhs) { return lhs || rhs; }
tribool tribool_EQ(tribool lhs, tribool rhs) { return lhs == rhs; }
tribool tribool_NE(tribool lhs, tribool rhs) { return lhs != rhs; }

void show_NOT(ostream &os) {
	show_op1("!", tribool_NOT, os);
}

void show_AND(ostream &os) {
	show_op2("&&", tribool_AND, os);
}

void show_OR(ostream &os) {
	show_op2("||", tribool_OR, os);
}

void show_EQ(ostream &os) {
	show_op2("==", tribool_EQ, os);
}

void show_NE(ostream &os) {
	show_op2("!=", tribool_NE, os);
}

#include <sstream>

#include "Util/CK/CK.h"

int main() {

	{
CK_section("Negation ..........................."				)
		ostringstream os;
		show_NOT(os);
CK_compare(	os.str(),
		"! false         => true"				"\n"
		"! true          => false"				"\n"
		"! indeterminate => indeterminate"			"\n"	)
	}

	{
CK_section("Logical AND ........................"				)
		ostringstream os;
		show_AND(os);
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
		show_OR(os);
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
		show_EQ(os);
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
		show_NE(os);
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

