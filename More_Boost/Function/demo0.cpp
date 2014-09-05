#include <boost/format.hpp>
	using boost::format;
	using boost::io::group;

#include <iostream>
	using namespace std;

const bool all[]= { false, true };
const bool *const all_begin= &all[0];
const bool *const all_end= &all[2];

void show_NOT(ostream &os) {
	for (const bool* rhs= all_begin; rhs < all_end; ++rhs) {
		os << format("! %|-5| => %||\n")
			% group(boolalpha, *rhs)
			% group(boolalpha, !*rhs);
	}
}

void show_AND(ostream &os) {
	for (const bool* lhs= all_begin; lhs < all_end; ++lhs) {
		for (const bool* rhs= all_begin; rhs < all_end; ++rhs) {
			os << format("%|-5| && %|-5| => %||\n")
				% group(boolalpha, *lhs)
				% group(boolalpha, *rhs)
				% group(boolalpha, *lhs && *rhs);
		}
	}
}

void show_OR(ostream &os) {
	for (const bool* lhs= all_begin; lhs < all_end; ++lhs) {
		for (const bool* rhs= all_begin; rhs < all_end; ++rhs) {
			os << format("%|-5| || %|-5| => %||\n")
				% group(boolalpha, *lhs)
				% group(boolalpha, *rhs)
				% group(boolalpha, *lhs || *rhs);
		}
	}
}

void show_EQ(ostream &os) {
	for (const bool* lhs= all_begin; lhs < all_end; ++lhs) {
		for (const bool* rhs= all_begin; rhs < all_end; ++rhs) {
			os << format("%|-5| == %|-5| => %||\n")
				% group(boolalpha, *lhs)
				% group(boolalpha, *rhs)
				% group(boolalpha, *lhs == *rhs);
		}
	}
}

void show_NE(ostream &os) {
	for (const bool* lhs= all_begin; lhs < all_end; ++lhs) {
		for (const bool* rhs= all_begin; rhs < all_end; ++rhs) {
			os << format("%|-5| != %|-5| => %||\n")
				% group(boolalpha, *lhs)
				% group(boolalpha, *rhs)
				% group(boolalpha, *lhs != *rhs);
		}
	}
}

#include <sstream>

#include "Util/CK/CK.h"

int main() {
	{
CK_section("Negation ..........................."		)
		ostringstream os;
		show_NOT(os);
CK_compare(	os.str(),
		"! false => true"			"\n"
		"! true  => false"			"\n"	)
	}

	{
CK_section("Logical AND ........................"		)
		ostringstream os;
		show_AND(os);
CK_compare(	os.str(),
		"false && false => false"		"\n"
		"false && true  => false"		"\n"
		"true  && false => false"		"\n"
		"true  && true  => true"		"\n"	)
	}

	{
CK_section("Logical OR ........................."		)
		ostringstream os;
		show_OR(os);
CK_compare(	os.str(),
		"false || false => false"		"\n"
		"false || true  => true"		"\n"
		"true  || false => true"		"\n"
		"true  || true  => true"		"\n"	)
	}

	{
CK_section("Equality ..........................."		)
		ostringstream os;
		show_EQ(os);
CK_compare(	os.str(),
		"false == false => true"		"\n"
		"false == true  => false"		"\n"
		"true  == false => false"		"\n"
		"true  == true  => true"		"\n"	)
	}

	{
CK_section("Unequality ........................."		)
		ostringstream os;
		show_NE(os);
CK_compare(	os.str(),
		"false != false => false"		"\n"
		"false != true  => true"		"\n"
		"true  != false => true"		"\n"
		"true  != true  => false"		"\n"	)
	}

}

