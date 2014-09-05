#include <boost/format.hpp>
	using boost::format;
	using boost::io::group;
#include <boost/function.hpp>
#include <boost/lambda/lambda.hpp>
	using boost::lambda::_1;
	using boost::lambda::_2;

#include <iostream>
	using namespace std;

const bool all[]= { false, true };
const bool *const all_begin= &all[0];
const bool *const all_end= &all[2];

inline
void show_op1(const char *opname, boost::function<bool(bool)> op, ostream &os) {
	for (const bool* rhs= all_begin; rhs < all_end; ++rhs) {
		os << format("%s %|-5| => %||\n")
			% opname
			% group(boolalpha, *rhs)
			% group(boolalpha, op(*rhs));
	}
}

inline
void show_op2(const char *opname, boost::function<bool(bool, bool)> op, ostream &os) {
	for (const bool* lhs= all_begin; lhs < all_end; ++lhs) {
		for (const bool* rhs= all_begin; rhs < all_end; ++rhs) {
			os << format("%|-5| %s %|-5| => %||\n")
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
CK_section("Negation ..........................."		)
		ostringstream os;
		show_op1("!", (! _1), os);
CK_compare(	os.str(),
		"! false => true"			"\n"
		"! true  => false"			"\n"	)
	}

	{
CK_section("Logical AND ........................"		)
		ostringstream os;
		show_op2("&&", (_1 && _2), os);
CK_compare(	os.str(),
		"false && false => false"		"\n"
		"false && true  => false"		"\n"
		"true  && false => false"		"\n"
		"true  && true  => true"		"\n"	)
	}

	{
CK_section("Logical OR ........................."		)
		ostringstream os;
		show_op2("||", (_1 || _2), os);
CK_compare(	os.str(),
		"false || false => false"		"\n"
		"false || true  => true"		"\n"
		"true  || false => true"		"\n"
		"true  || true  => true"		"\n"	)
	}

	{
CK_section("Equality ..........................."		)
		ostringstream os;
		show_op2("==", (_1 == _2), os);
CK_compare(	os.str(),
		"false == false => true"		"\n"
		"false == true  => false"		"\n"
		"true  == false => false"		"\n"
		"true  == true  => true"		"\n"	)
	}

	{
CK_section("Unequality ........................."		)
		ostringstream os;
		show_op2("!=", (_1 != _2), os);
CK_compare(	os.str(),
		"false != false => false"		"\n"
		"false != true  => true"		"\n"
		"true  != false => true"		"\n"
		"true  != true  => false"		"\n"	)
	}

}

