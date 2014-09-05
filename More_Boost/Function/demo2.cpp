#include <boost/format.hpp>
	using boost::format;
	using boost::io::group;
#include <boost/function.hpp>

#include <iostream>
	using namespace std;

const bool all[]= { false, true };
const bool *const all_begin= &all[0];
const bool *const all_end= &all[2];


template<class T>
inline
void show_op1(T op, ostream &os) {
	for (const bool* rhs= all_begin; rhs < all_end; ++rhs) {
		os << format("%s %|-5| => %||\n")
			% op.name()
			% group(boolalpha, *rhs)
			% group(boolalpha, op(*rhs));
	}
}

template<class T>
inline
void show_op2(T op, ostream &os) {
	for (const bool* lhs= all_begin; lhs < all_end; ++lhs) {
		for (const bool* rhs= all_begin; rhs < all_end; ++rhs) {
			os << format("%|-5| %s %|-5| => %||\n")
				% group(boolalpha, *lhs)
				% op.name()
				% group(boolalpha, *rhs)
				% group(boolalpha, op(*lhs, *rhs));
		}
	}
}

struct bool_NOT {
	bool operator()(bool rhs) {
		return !rhs;
	}
	static const char* name() { return "!"; }
};

struct bool_AND {
	bool operator()(bool lhs, bool rhs) {
		return lhs && rhs;
	}
	static const char* name() { return "&&"; }
};

struct bool_OR {
	bool operator()(bool lhs, bool rhs) {
		return lhs || rhs;
	}
	static const char* name() { return "||"; }
};

struct bool_EQ {
	bool operator()(bool lhs, bool rhs) {
		return lhs == rhs;
	}
	static const char* name() { return "=="; }
};

struct bool_NE {
	bool operator()(bool lhs, bool rhs) {
		return lhs != rhs;
	}
static const char* name() { return "="; }
};

#include <sstream>

#include "Util/CK/CK.h"

int main() {

	{
CK_section("Negation ..........................."		)
		ostringstream os;
		show_op1(bool_NOT(), os);
CK_compare(	os.str(),
		"! false => true"			"\n"
		"! true  => false"			"\n"	)
	}

	{
CK_section("Logical AND ........................"		)
		ostringstream os;
		show_op2(bool_AND(), os);
CK_compare(	os.str(),
		"false && false => false"		"\n"
		"false && true  => false"		"\n"
		"true  && false => false"		"\n"
		"true  && true  => true"		"\n"	)
	}

	{
CK_section("Logical OR ........................."		)
		ostringstream os;
		show_op2(bool_OR(), os);
CK_compare(	os.str(),
		"false || false => false"		"\n"
		"false || true  => true"		"\n"
		"true  || false => true"		"\n"
		"true  || true  => true"		"\n"	)
	}

	{
CK_section("Equality ..........................."		)
		ostringstream os;
		show_op2(bool_EQ(), os);
CK_compare(	os.str(),
		"false == false => true"		"\n"
		"false == true  => false"		"\n"
		"true  == false => false"		"\n"
		"true  == true  => true"		"\n"	)
	}

	{
CK_section("Unequality ........................."		)
		ostringstream os;
		show_op2(bool_NE(), os);
CK_compare(	os.str(),
		"false != false => false"		"\n"
		"false != true  => true"		"\n"
		"true  != false => true"		"\n"
		"true  != true  => false"		"\n"	)
	}

}

